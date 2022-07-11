#include "Hash.hpp"

Hash::Hash(int hashTableSize) {
  errorAssert(hashTableSize > 0, "Null Hash Table dimension");
  this->hashTableSize = hashTableSize;

  this->Table = (Tree*) malloc(this->hashTableSize * sizeof(Tree));
  errorAssert(Table != NULL, "Failed to allocate Hash Table memory");
}

void Hash::insert(int userId, Email* email) {
  int hashTableInsertionIdx = this->getHashIdx(userId);
  this->Table[hashTableInsertionIdx].insert(email);
}

bool Hash::pop(int userId, int emailId) {
  int hashTableInsertionIdx = this->getHashIdx(userId);
  return this->Table[hashTableInsertionIdx].pop(emailId, userId);
}

Email* Hash::searchEmail(int userId, int emailId) {
  int hashTableSearchIdx = this->getHashIdx(userId);

  Email *searchedMail = this->Table[hashTableSearchIdx].search(emailId);

  if(searchedMail != NULL && searchedMail->getEmailUserId() == userId) 
    return searchedMail;
  else
    return NULL;
}

int Hash::getHashIdx(int key) {
  return key % this->hashTableSize;
}

Hash::~Hash() {
  this->hashTableSize = -1;
  free(this->Table);
}