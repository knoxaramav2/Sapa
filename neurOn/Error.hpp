#ifndef ERR
#define ERR

#include <string>

using namespace std;

//Warnings
  //General
  //File
  #define W_UNKN_EXTENSION  0x20
  //Lexile
  //Settings

//Errors
  //General
  //File
  #define E_FILE_DNE        0x120
  #define E_INV_FORMAT      0x121
  //Lexile
  //Settings

//errorCode, line, msg
void printError(unsigned, unsigned, string);

#endif
