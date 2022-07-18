#ifndef TREEH
#define TREEH

#include "Node.hpp"
#include "Email.hpp"
#include "memlog.h"

class Node;
class Tree {
  public:
    /**
     * @brief Default constructor for Tree class instance. Responsible for initialize
     * the Tree attributes.
     */
    Tree();
    /**
     * @brief Function responsible for inserting an email at the Tree in the 
     * correct position according to the email id, maintaining 
     * the Binary Tree integrity. 
     *
     * @param email The email to be inserted in the Tree.
     */
    void insert(Email* email);
    /**
     * @brief Function responsible for removing and free an email from the 
     * Tree according to the email and user ids.
     *
     * @param emailId The email id that is intended to be removed.
     * @param userId The id from the user that is supposed to be the email sender
     * from the email that is intended to be removed.
     * 
     * @return Returns true when the email could be found and deleted and false 
     * when it wasn't.
     */
    bool pop(int emailId, int userId);
    /**
     * @brief Function responsible for searching an email by its id.
     *
     * @param emailId The email id that is intended to be found.
     * 
     * @return Returns the email searched when it could be found and NULL otherwise.
     */
    Email* search(int emailId);
    /**
     * @brief Function responsible for removing and freeing all the elements of 
     * the Tree and resetting its attributes.
     */
    void cleanUp();
    /**
     * @brief Default destructor of the class, that will clean it up when called and free the allocated memory.
     */
    ~Tree();
  private:
    /**
     * @brief Function responsible for inserting an email at the Tree using an 
     * recursive approach to find the correct place to insertion.
     *
     * @param currentNode The Tree node that is currently being analyzed.
     * @param email The email to be inserted in the Tree.
     */
    void recursiveInsert(Node* &currentNode, Email* email);
    /**
     * @brief Function responsible for removing and freeing an email from the 
     * Tree using an recursive approach to find the correct place of removal.
     *
     * @param currentNode The Tree node that is currently being analyzed.
     * @param emailId The email id that is intended to be removed.
     * @param userId The id from the user that is supposed to be the email sender
     * from the email that is intended to be removed.
     * 
     * @return Returns true when the email could be found and deleted and false 
     * when it wasn't.
     */
    bool recursivePop(Node* &currentNode, int emailId, int userId);
    /**
     * @brief Function responsible for searching an appropriate ancestor to the 
     * childs of a node currently being deleted.
     *
     * @param nodeBeingRemoved The Tree node that is being deleted an needs to 
     * transfer it's childs to a new parent.
     * @param ancestor The Tree node that is being considered as a new parent.
     */
    void transferChildAncestor(Node* nodeBeingRemoved, Node* &ancestor);
    /**
     * @brief Function responsible for searching an email by its id using an 
     * recursive approach to find the desired email.
     *
     * @param currentNode The Tree node that is currently being analyzed.
     * @param emailId The email id that is intended to be found.
     * 
     * @return Returns the email searched when it could be found and NULL otherwise.
     */
    Email* recursiveSearch(Node* currentNode, int emailId);
    /**
     * @brief Function responsible for iterating over all Tree elements, deleting 
     * and freeing them.
     *
     * @param currentNode The Tree node that is currently being analyzed.
     */
    void recursiveDeleteAll(Node* currentNode);
    Node* root;
}; 
#endif