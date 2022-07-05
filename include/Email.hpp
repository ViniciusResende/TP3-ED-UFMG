#ifndef EMAILH
#define EMAILH

#include <string>
#include "memlog.h"

class Email {
  public:  
    Email(int id, std::string message);
    int getEmailId();

    ~Email();

  private:
    std::string message;
    int _id;
};

#endif
