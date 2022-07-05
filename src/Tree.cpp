#include "Tree.hpp"

Tree::Tree() {
  this->root = NULL;
}

void Tree::insert(Email* email) {
  this->recursiveInsertion(this->root, email);
}

void Tree::recursiveInsertion(Node* &currentNode, Email* email) {
  if(currentNode != NULL) {
    if(email->getEmailId() < currentNode->email->getEmailId())
      recursiveInsertion(currentNode->left, email);
    else
      recursiveInsertion(currentNode->right, email);

    return;
  }

  currentNode = new Node(email);
}

Email* Tree::search(int emailId) {
  return this->recursiveSearch(this->root, emailId);
}

Email* Tree::recursiveSearch(Node* currentNode, int emailId) {
  if(currentNode == NULL) {
    return NULL;
  }

  if(currentNode->email->getEmailId() < emailId)
    recursiveSearch(currentNode->right, emailId);
  else if(currentNode->email->getEmailId() > emailId)
    recursiveSearch(currentNode->left, emailId);
  else
    return currentNode->email;
}

void Tree::cleanUp() {
  this->recursiveDeleteAll(this->root);
  this->root = NULL;
}

void Tree::recursiveDeleteAll(Node* currentNode) {
  if(currentNode != NULL) {
    recursiveDeleteAll(currentNode->left);
    recursiveDeleteAll(currentNode->right);
    delete currentNode;
  }
}


Tree::~Tree() {
  cleanUp();
}