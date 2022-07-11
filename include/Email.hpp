#ifndef EMAILH
#define EMAILH

#include <string>
#include "memlog.h"

class Email {
  public:  
    Email(int id, int userId, std::string message);
    int getEmailId();
    int getEmailUserId();
    std::string getEmailMessage();

    ~Email();

  private:
    std::string message;
    int _id;
    int _userId;
};

#endif
