#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string.h>
#include "CONSTANTS.hpp"
#include "Hash.hpp"
#include "memlog.h" 
#include "msgassert.h"

struct ConfigStruct {
  int hashTableSize;
  bool regmem;
  char inputFile[100], outputFile[100], logname[100] = "/tmp/email_server_log.out";
};

ConfigStruct config;

/**
 * @brief Print at console the possible parameters of the application and describe them.
 */
void menu() {
  fprintf(stderr,"Google Mail Server\n");
  fprintf(stderr,"-[i|I] <file>\t(Input File)\n");
  fprintf(stderr,"-[o|O] <file>\t(Output file)\n");
  fprintf(stderr,"-l \t\t(register memory access)\n");
}

/**
 * @brief Function responsible to read run time parameters and set config values.
 * 
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
void parse_args(int argc,char ** argv) {
  extern char * optarg;

  int c;

  config.regmem = false;
  config.inputFile[0] = 0;
  config.outputFile[0] = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "i:I:o:O:l")) != EOF)
    switch(tolower(c)) {
      case 'i': 
        strcpy(config.inputFile, optarg);
        break;
      case 'o': 
        strcpy(config.outputFile, optarg);
        break;
      case 'l': 
        config.regmem = true;
        break;
      default:
        menu();
        exit(1);
        break;
    }

  errorAssert(strlen(config.inputFile) > 0,
    "Google Mail Server - input file name must be previously defined");
  errorAssert(strlen(config.outputFile) > 0,
    "Google Mail Server - output file name must be previously defined");  
}

void handleMailInsertion(std::ifstream &inputFile, Hash *globalHash) {
  int userId = -1;
  int emailId = -1;
  int messageLength = -1;

  inputFile >> userId;
  inputFile >> emailId;
  inputFile >> messageLength;

  errorAssert(userId >= 0, "User id wasn't provided at mail insertion");
  errorAssert(emailId >= 0, "Email id wasn't provided at mail insertion");
  errorAssert(messageLength >= 0, "Invalid message length provided at mail insertion");
  errorAssert(messageLength <= MAIL_MESSAGE_MAX_SIZE, "Number of words in the mail message exceeds the limit of 200");

  std::string emailMessage;
  std::string currentWord;

  for (int i = 0; i < messageLength; i++) {
    inputFile >> currentWord;
    emailMessage.append(currentWord);
    emailMessage.append(" ");

    errorAssert(currentWord.size() <= MAIL_WORD_MAX_SIZE, "Mail word exceeds character limit");
    errorAssert(currentWord.size() > MAIL_WORD_MIN_SIZE, "Mail word is smaller than minimum size");
  }
  emailMessage.pop_back();

  Email *newMail = new Email(emailId, emailMessage);
  globalHash->insert(userId, newMail);
}

void handleMailSearch(std::ifstream &inputFile, Hash *globalHash) {
  int userId = -1;
  int emailId = -1;

  inputFile >> userId;
  inputFile >> emailId;

  errorAssert(userId >= 0, "User id wasn't provided at mail search");
  errorAssert(emailId >= 0, "Email id wasn't provided at mail search");

  Email *searchedMail = globalHash->searchEmail(userId, emailId);

  std::cout << SEARCH_MAIL_TAG << " " << userId << " " << emailId << ": ";

  if(searchedMail != NULL)
    std::cout << searchedMail->getEmailMessage();
  else 
    std::cout << SEARCHED_MAIL_NOT_FOUND;

  std::cout << std::endl;
}

void handleMailDelete(std::ifstream &inputFile) {

}

void inputFileReader(char inputFileName[], Hash *globalHash) {
  std::ifstream inputFile(inputFileName);
  errorAssert(inputFile.is_open(), "\nFailed to open input file");

  inputFile >> config.hashTableSize;
  globalHash = new Hash(config.hashTableSize);

  std::string buffer;

  while (!inputFile.eof()) {
    inputFile >> buffer;
    
    if(buffer == INSERT_MAIL_TAG)
      handleMailInsertion(inputFile, globalHash);
    else if(buffer == SEARCH_MAIL_TAG)
      handleMailSearch(inputFile, globalHash);
    else if(buffer == DELETE_MAIL_TAG)
      handleMailDelete(inputFile);
  }
}

/**
 * @brief Main Function: Responsible for initializing the MemLog lib depending on the run-time 
 * parameters and calling the functions inputReadVectors followed by 
 * sortWordsAccordingToLexOrder, and finally printOutputResult.
 * 
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
int main(int argc, char ** argv) {
  parse_args(argc,argv);

  startMemLog(config.logname);

  if (config.regmem) 
    activateMemLog();
  else 
    deactivateMemLog();

  Hash *globalHash = NULL;

  inputFileReader(config.inputFile, globalHash);

  // globalTree->print();
  // std::cout << std::endl;

  return endUpMemLog();
}
