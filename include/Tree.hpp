#ifndef TREEH
#define TREEH

#include "Node.hpp"
#include "Email.hpp"
#include "memlog.h"

class Node;
class Tree {
  public:
    Tree();
    void insert(Email* email);
    Email* search(int emailId);
    void cleanUp();
    ~Tree();
  private:
    void recursiveInsertion(Node* &currentNode, Email* email);
    Email* recursiveSearch(Node* currentNode, int emailId);
    void recursiveDeleteAll(Node* currentNode);
    Node* root;
}; 
#endif