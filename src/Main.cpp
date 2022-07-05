#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string.h>
#include "memlog.h" 
#include "msgassert.h"

struct ConfigStruct {
  int quickSortPivot, sortingAlgorithmBreakpoint;
  bool regmem;
  char inputFile[100], outputFile[100], logname[100] = "/tmp/email_server_log.out";
};

ConfigStruct config;

/**
 * @brief Print at console the possible parameters of the application and describe them.
 */
void menu() {
  fprintf(stderr,"Google Mail Server\n");
  fprintf(stderr,"-[i|I] <file>\t(Input File)\n");
  fprintf(stderr,"-[o|O] <file>\t(output matrix file)\n");
  fprintf(stderr,"-[m|M] <number>\t(Quick Sort Pivot Median)\n");
  fprintf(stderr,"-[s|S] <number>\t(Breakpoint Size to Change Sort Algorithm)\n");
  fprintf(stderr,"-l \t\t(register memory access)\n");
}

/**
 * @brief Function responsible to read run time parameters and set config values.
 * 
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
void parse_args(int argc,char ** argv) {
  extern char * optarg;

  int c;

  config.quickSortPivot = -1;
  config.sortingAlgorithmBreakpoint = -1;
  config.regmem = false;
  config.inputFile[0] = 0;
  config.outputFile[0] = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "i:I:o:O:m:M:s:S:lp:")) != EOF)
    switch(tolower(c)) {
      case 'i': 
        strcpy(config.inputFile, optarg);
        break;
      case 'o': 
        strcpy(config.outputFile, optarg);
        break;
      case 'm':
        errorAssert(atoi(optarg) > 0, "Invalid Quick Sort pivot median provided");
        config.quickSortPivot = atoi(optarg);
        break;
      case 's':
        errorAssert(atoi(optarg) > 0, "Invalid Breakpoint Size provided");
        config.sortingAlgorithmBreakpoint = atoi(optarg);
        break;
      case 'p': 
        strcpy(config.logname, optarg);
        break;
      case 'l': 
        config.regmem = true;
        break;
      default:
        menu();
        exit(1);
        break;
    }

  errorAssert(strlen(config.inputFile) > 0,
    "Analyze and Sort - input file name must be previously defined");
  errorAssert(strlen(config.outputFile) > 0,
    "Analyze and Sort - output file name must be previously defined");  
  if(config.sortingAlgorithmBreakpoint == -1) {
    warnAssert(false, "Algorithm Breakpoint Size wasn't provided keeping default of 20");
    config.sortingAlgorithmBreakpoint = 20;
  }
  if(config.quickSortPivot == -1) {
    warnAssert(false, "Quick Sort pivot median wasn't provided keeping default of 1");
    config.quickSortPivot = 1;
  }
}

/**
 * @brief Main Function: Responsible for initializing the MemLog lib depending on the run-time 
 * parameters and calling the functions inputReadVectors followed by 
 * sortWordsAccordingToLexOrder, and finally printOutputResult.
 * 
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
int main(int argc, char ** argv) {
  parse_args(argc,argv);

  startMemLog(config.logname);

  if (config.regmem) 
    activateMemLog();
  else 
    deactivateMemLog();

  return endUpMemLog();
}
