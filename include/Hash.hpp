#ifndef HASHH
#define HASHH

#include "Email.hpp"
#include "msgassert.h"
#include "memlog.h"
#include "Tree.hpp"

class Hash {
  public:  
    Hash(int hashTableSize);
    void insert(int userId, Email* email);
    bool pop(int userId, int emailId);
    Email* searchEmail(int userId, int emailId);
    int getHashIdx(int key);
    ~Hash();

  private:
    int hashTableSize;
    Tree *Table;
};

#endif
