#ifndef ERROR
#define ERROR

#include <string>

using namespace std;

#define MIN_WARNC  1
#define MAX_WARNC  10000
#define MIN_ERRC   10001
#define MAX_ERRC   20000

extern bool suppressError;
extern bool suppressWarning;
extern bool fatalWarning;

extern unsigned numWarnings;
extern unsigned numErrors;

//Warning Codes 1-10,000
  //File
#define WRN_UNEXPECT_EXT    00001//Unexpected file extension
  //Format
  //General
  //Syntax
  //Config
  //Type
//Error Codes 10,001 - 20,000
  //File
#define ERR_NO_CNS          10001//No CNS file found
#define ERR_NO_CIPHER       10003//Cipher file not found
#define ERR_FNF             10004//File not found
#define ERR_FWRITE          10005//Could not write to file
#define ERR_FREAD           10006//Could not read file
  //General
#define ERR_UNRES_SYMBOL    12001//Unresolved symbol
#define ERR_UNREC_CHAR      12002//Unrecognized symbol
#define ERR_REDEF_SYMB      12003//Redfined symbol in scope
  //Syntax
#define ERR_ILL_OP_ARG      13001//Illegal operator arguments
  //Config
#define ERR_SETTING         14001//Invalid setting
#define ERR_SETTING_VALUE   14002//Invalid setting value
  //Type
#define ERR_INV_TYPE        15001//Invalid type

//Error code, index, code file, comment
void postError(unsigned, int, string&, string);

bool isFatal();

#endif
