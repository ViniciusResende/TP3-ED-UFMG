#include "Tree.hpp"

Tree::Tree() {
  this->root = NULL;
}

void Tree::insert(Email* email) {
  this->recursiveInsert(this->root, email);
}

void Tree::recursiveInsert(Node* &currentNode, Email* email) {
  if(currentNode != NULL) {
    if(email->getEmailId() < currentNode->email->getEmailId())
      recursiveInsert(currentNode->left, email);
    else
      recursiveInsert(currentNode->right, email);

    return;
  }

  currentNode = new Node(email);
}

bool Tree::pop(int emailId) {
  return this->recursivePop(this->root, emailId);
}

bool Tree::recursivePop(Node* &currentNode, int emailId) {
  Node *aux;

  if(currentNode == NULL)
    return false;
  
  if(emailId < currentNode->email->getEmailId())
    return this->recursivePop(currentNode->left, emailId);
  else if (emailId > currentNode->email->getEmailId())
    return this->recursivePop(currentNode->right, emailId);
  else {
    if(currentNode->right == NULL) {
      aux = currentNode;
      currentNode = currentNode->left;
      free(aux);
    } else if(currentNode->left == NULL) {
      aux = currentNode;
      currentNode = currentNode->right;
      free(aux);
    } else
      this->transferChildAncestor(currentNode, currentNode->left);

    return true;
  }
}

void Tree::transferChildAncestor(Node* nodeBeingRemoved, Node* ancestor) {
  if(ancestor->right != NULL) 
    return this->transferChildAncestor(nodeBeingRemoved, ancestor->right);
  
  nodeBeingRemoved->email = ancestor->email;
  nodeBeingRemoved = ancestor;
  ancestor = ancestor->left;
  free(nodeBeingRemoved);
}

Email* Tree::search(int emailId) {
  return this->recursiveSearch(this->root, emailId);
}

Email* Tree::recursiveSearch(Node* currentNode, int emailId) {
  if(currentNode == NULL) {
    return NULL;
  }

  if(currentNode->email->getEmailId() < emailId)
    return recursiveSearch(currentNode->right, emailId);
  else if(currentNode->email->getEmailId() > emailId)
    return recursiveSearch(currentNode->left, emailId);
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