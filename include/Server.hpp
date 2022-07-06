#ifndef SERVERH
#define SERVERH

#include <fstream>
#include "Email.hpp"
#include "msgassert.h"
#include "memlog.h"
#include "Hash.hpp"

class Server {
  public:  
    Server(char inputFileName[], char outputFileName[]);
    void run();
    ~Server();

  private:
    void inputFileReader();
    void handleMailInsertion();
    void handleMailSearch();
    void handleMailDelete();

    Hash* userTable;
    std::ifstream inputFile;
    std::ofstream outputFile;
};
#endif
