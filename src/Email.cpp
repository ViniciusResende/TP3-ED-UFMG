#include "Email.hpp"

Email::Email(int id, int userId, std::string message) {
  this->_id = id;
  this->_userId = userId;
  this->message = message;
}

int Email::getEmailId() {
  return this->_id;
}

int Email::getEmailUserId() {
  return this->_userId;
}

std::string Email::getEmailMessage() {
  return this->message;
}

Email::~Email() {
  this->message.clear();
  this->_id = -1;
  this->_userId = -1;
}