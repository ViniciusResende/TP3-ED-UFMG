#ifndef SERVERH
#define SERVERH

#include <fstream>
#include "Email.hpp"
#include "msgassert.h"
#include "memlog.h"
#include "Hash.hpp"

class Server {
  public:  
    /**
     * @brief Default constructor for Server class instance. Responsible for initialize
     * the Server data structures and attributes.
     * 
     * @param inputFileName Name of the Server input file.
     * @param outputFileName Name of the Server output file.
     */
    Server(char inputFileName[], char outputFileName[]);

    /**
     * @brief Function responsible for executing all Server responsibilities from 
     * reading the input file to print the operations results in the output file.
     */
    void run();

    /**
     * @brief Default destructor of the class, that will clean it up when called and free the allocated memory.
     */
    ~Server();

  private:
    /**
     * @brief Orchestrator function responsible for reading the server input file 
     * and call the correct methods according with what is passed by the input 
     * file.
     */
    void inputFileReader();
    /**
     * @brief Function responsible for executing the insertion of an email in the 
     * users Hash table and, by the end, print the operation metrics in the 
     * output file.
     */
    void handleMailInsertion();
    /**
     * @brief Function responsible for executing the search operation of an email 
     * in the users Hash table and, by the end, print the operation metrics in 
     * the output file.
     */
    void handleMailSearch();
    /**
     * @brief Function responsible for executing the delete operation of an email 
     * in the users Hash table and, by the end, print the operation metrics in 
     * the output file.
     */
    void handleMailDelete();

    Hash* userTable;
    std::ifstream inputFile;
    std::ofstream outputFile;
};
#endif
