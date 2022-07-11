#ifndef HASHH
#define HASHH

#include "Email.hpp"
#include "msgassert.h"
#include "memlog.h"
#include "Tree.hpp"

class Hash {
  public:  
    /**
     * @brief Default constructor for Hash class instance. Responsible for initialize
     * the Hash table and allocate the needed space.
     * 
     * @param hashTableSize Size of the Hash table.
     */
    Hash(int hashTableSize);
    
    /**
     * @brief Function responsible for inserting an email from an given user at the 
     * Hash table in the correct tree according to the user id, maintaining the 
     * Hash integrity. 
     *
     * @param userId The user id of the email sender.
     * @param email The email to be inserted in the Hash.
     */
    void insert(int userId, Email* email);
    /**
     * @brief Function responsible for removing and free an email from the Tree 
     * at a certain index on the Hash according to the email and user ids.
     *
     * @param emailId The email id that is intended to be removed.
     * @param userId The id from the user that is supposed to be the email sender
     * from the email that is intended to be removed.
     * 
     * @return Returns true when the email could be found and deleted and false 
     * when it wasn't.
     */
    bool pop(int userId, int emailId);
    /**
     * @brief Function responsible for searching an email by its id and it's sender user id.
     *
     * @param userId The id from the user that is supposed to have sent the searched email.
     * @param emailId The email id that is intended to be found.
     * 
     * @return Returns the email searched when it could be found and NULL otherwise.
     */
    Email* searchEmail(int userId, int emailId);
    /**
     * @brief Function responsible for returning the Hash table index for a given key (userId).
     *
     * @param key The key to be converted to a Hash table index.
     * 
     * @return Returns the index where the key should be stored in the Hash table.
     */
    int getHashIdx(int key);

    /**
     * @brief Default destructor of the class, that will clean it up when called and free the allocated memory.
     */
    ~Hash();

  private:
    int hashTableSize;
    Tree *Table;
};

#endif
