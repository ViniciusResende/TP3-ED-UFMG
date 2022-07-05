#include "Email.hpp"

Email::Email(int id, std::string message) {
  this->_id = id;
  this->message = message;
}

int Email::getEmailId() {
  return this->_id;
}

Email::~Email() {
  this->message.clear();
  this->_id = -1;
}