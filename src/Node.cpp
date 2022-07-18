#include "Node.hpp"

Node::Node(Email* email) {
  errorAssert(email != nullptr, "Email must be previously defined to be inserted at a Tree");
  this->email = email;

  this->left = NULL;
  this->right = NULL;
}

Node::~Node() {};