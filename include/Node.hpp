#ifndef NODEH
#define NODEH

#include "Email.hpp"
#include "memlog.h"
#include "Tree.hpp"

class Node {
  public:  
    /**
     * @brief Default constructor for Node class instance. Responsible for initialize
     * the Node attributes.
     * 
     * * @param email The email to be stored in the  node.
     */
    Node(Email* email);

    /**
     * @brief Default destructor of the class, that will clean it up when called and free the allocated memory.
     */
    ~Node();

  private:
    Email* email;
    Node* left;
    Node* right;

  friend class Tree;
};

#endif
