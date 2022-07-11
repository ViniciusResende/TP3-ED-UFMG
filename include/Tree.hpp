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
    bool pop(int emailId, int userId);
    Email* search(int emailId);
    void cleanUp();
    ~Tree();
  private:
    void recursiveInsert(Node* &currentNode, Email* email);
    bool recursivePop(Node* &currentNode, int emailId, int userId);
    void transferChildAncestor(Node* nodeBeingRemoved, Node* ancestor);
    Email* recursiveSearch(Node* currentNode, int emailId);
    void recursiveDeleteAll(Node* currentNode);
    Node* root;
}; 
#endif