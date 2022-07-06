#include "Server.hpp"
#include "CONSTANTS.hpp"
#include <iostream>

Server::Server(char inputFileName[], char outputFileName[]) {
  this->userTable = NULL;

  this->inputFile = std::ifstream(inputFileName);
  errorAssert(this->inputFile.is_open(), "Failed to open input file");

  this->outputFile = std::ofstream(outputFileName);
  errorAssert(this->inputFile.is_open(), "Failed to open input file");
}

void Server::run() {
  this->inputFileReader();
}

void Server::inputFileReader() {  
  int hashTableSize;
  this->inputFile >> hashTableSize;
  this->userTable = new Hash(hashTableSize);

  std::string buffer;

  while (!inputFile.eof()) {
    inputFile >> buffer;
    
    if(buffer == INSERT_MAIL_TAG)
      this->handleMailInsertion();
    else if(buffer == SEARCH_MAIL_TAG)
      this->handleMailSearch();
    else if(buffer == DELETE_MAIL_TAG)
      this->handleMailDelete();
  }
}

void Server::handleMailInsertion() {
  int userId = -1;
  int emailId = -1;
  int messageLength = -1;

  this->inputFile >> userId;
  this->inputFile >> emailId;
  this->inputFile >> messageLength;

  errorAssert(userId >= 0, "User id wasn't provided at mail insertion");
  errorAssert(emailId >= 0, "Email id wasn't provided at mail insertion");
  errorAssert(messageLength >= 0, "Invalid message length provided at mail insertion");
  errorAssert(messageLength <= MAIL_MESSAGE_MAX_SIZE, "Number of words in the mail message exceeds the limit of 200");

  std::string emailMessage;
  std::string currentWord;

  for (int i = 0; i < messageLength; i++) {
    this->inputFile >> currentWord;
    emailMessage.append(currentWord);
    emailMessage.append(" ");

    errorAssert(currentWord.size() <= MAIL_WORD_MAX_SIZE, "Mail word exceeds character limit");
    errorAssert(currentWord.size() > MAIL_WORD_MIN_SIZE, "Mail word is smaller than minimum size");
  }
  emailMessage.pop_back();

  Email *newMail = new Email(emailId, emailMessage);
  this->userTable->insert(userId, newMail);

  this->outputFile 
    << "OK: MENSAGEM " 
    << emailId 
    << " PARA " 
    << userId 
    << " ARMAZENADA EM " 
    << userTable->getHashIdx(userId)
    << std::endl;
}

void Server::handleMailSearch() {
  int userId = -1;
  int emailId = -1;

  inputFile >> userId;
  inputFile >> emailId;

  errorAssert(userId >= 0, "User id wasn't provided at mail search");
  errorAssert(emailId >= 0, "Email id wasn't provided at mail search");

  Email *searchedMail = this->userTable->searchEmail(userId, emailId);

  this->outputFile << SEARCH_MAIL_TAG << " " << userId << " " << emailId << ": ";

  if(searchedMail != NULL)
    this->outputFile << searchedMail->getEmailMessage();
  else 
    this->outputFile << SEARCHED_MAIL_NOT_FOUND_MESSAGE;

  this->outputFile << std::endl;
}

void Server::handleMailDelete() {
  int userId = -1;
  int emailId = -1;

  inputFile >> userId;
  inputFile >> emailId;

  errorAssert(userId >= 0, "User id wasn't provided at mail search");
  errorAssert(emailId >= 0, "Email id wasn't provided at mail search");

  bool mailWasSuccessfullyDeleted = this->userTable->pop(userId, emailId);
  this->outputFile 
    << (mailWasSuccessfullyDeleted 
      ? MAIL_SUCCESS_ON_DELETE_MESSAGE 
      : MAIL_FAIL_ON_DELETE_MESSAGE) 
    << std::endl;
}