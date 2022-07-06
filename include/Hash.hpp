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
    void pop(int userId, int emailId);
    Email* searchEmail(int userId, int emailId);
    ~Hash();

  private:
    int hashTableSize;
    int getHashIdx(int key);
    Tree *Table;
};

#endif
