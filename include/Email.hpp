#ifndef EMAILH
#define EMAILH

#include <string>
#include "memlog.h"
#include "msgassert.h"

class Email {
  public:  
    /**
     * @brief Default constructor for Email class instance. 
     *
     * @param id The email unique number identifier.
     * @param userId The unique number identifier from the user that sent the email.
     * @param message Body message of the email sent.
     */
    Email(int id, int userId, std::string message);
    /**
     * @brief Returns the integer value that represents the email unique number identifier.
     *
     * @return Returns the value stored in the _id attribute.
     */
    int getEmailId();
    /**
     * @brief Returns the integer value that represents the unique number 
     * identifier from the user that sent the email.
     *
     * @return Returns the value stored in the _userId attribute.
     */
    int getEmailUserId();
    /**
     * @brief Returns the string value that represents the body message of the email.
     *
     * @return Returns the value stored in the message attribute.
     */
    std::string getEmailMessage();

    /**
     * @brief Default destructor of the class, that will clean it up when called.
     */
    ~Email();

  private:
    std::string message;
    int _id;
    int _userId;
};

#endif
