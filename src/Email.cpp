#include "Email.hpp"

Email::Email(int id, int userId, std::string message) {
  this->_id = id;
  this->_userId = userId;

  errorAssert(!message.empty(), "Can't create email with empty string message.");
  this->message = message;

  WRITEMEMLOG((long int) (&(this->_id)), sizeof(int), this->_userId);
}

int Email::getEmailId() {
  READMEMLOG((long int) (&(this->_id)), sizeof(int), this->_userId);
  return this->_id;
}

int Email::getEmailUserId() {
  return this->_userId;
}

std::string Email::getEmailMessage() {
  return this->message;
}

Email::~Email() {
  warnAssert(this->_id != -1, "Mail instance has already been destroyed.");

  this->message.clear();
  this->_id = -1;
  this->_userId = -1;
}