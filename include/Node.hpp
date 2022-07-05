#ifndef NODEH
#define NODEH

#include "Email.hpp"
#include "memlog.h"
#include "Tree.hpp"

class Node {
  public:  
    Node(Email* email);

    ~Node();

  private:
    Email* email;
    Node* left;
    Node* right;

  friend class Tree;
};

#endif
