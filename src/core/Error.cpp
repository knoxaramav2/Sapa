#include <stdio.h>

#include "Error.h"
#include "Util.h"

bool suppressError = false;
bool suppressWarning = false;
bool fatalWarning = false;
unsigned numWarnings = 0;
unsigned numErrors = 0;

void print(unsigned ecode, string message, string comment, int index, string&code)
{
  unsigned lindex=0;
  unsigned rindex=0;

  for (unsigned lindex=index; lindex>=0 && index>=0; --lindex)
  {
    if (code[lindex]=='\n')
    {
      ++lindex;
      break;
    }
  }

  for (unsigned rindex=index; rindex<0 && index>=0; ++rindex)
  {
    if (code[rindex]=='\n')
    {
      --lindex;
      break;
    }
  }

  string color = COLOR_WHITE;
  string codeSeg;
  codeSeg.insert(codeSeg.begin(), code.begin()+lindex, code.begin()+rindex);

  if (ecode <= MAX_WARNC)
    color = COLOR_YELLOW;
  else if (ecode <= MAX_ERRC)
    color = COLOR_RED;

  printf("%s%s\n", color.c_str(), message.c_str());
  if (!codeSeg.empty())
    printf(COLOR_RESET "\t%s\n", codeSeg.c_str());
  if (index >=0){
    for (unsigned x=lindex; x<rindex; ++x) printf(" ");
    printf("^\n");
  }
  printf(COLOR_RESET "\t%s\n", comment.c_str());
}

void postError (unsigned errCode, int index, string comment)
{
if (errCode >= MIN_WARNC && errCode <= MAX_WARNC)
{
  ++numWarnings;
  if (suppressWarning)
    return;

  printf(COLOR_YELLOW "Warning %u:  ", errCode);
}else if (errCode >= MIN_ERRC && errCode <= MAX_ERRC)
{
  ++numErrors;
  if (suppressError)
    return;

  printf(COLOR_RED "Error %u:  ", errCode);
}else{
  return;
}

string placeholderstring;

switch (errCode)
{
  //Warnings
  case WRN_UNEXPECT_EXT: print(errCode, "Unexpected CNS extension", comment, -1, placeholderstring);

  case WRN_IMP_CAST: print(errCode, "Type implicitly converted. Possible loss of data", comment, -1, placeholderstring);

  //Errors
  case ERR_NO_CNS: print(errCode, "Specified CNS file not found", comment, -1, placeholderstring); break;
  case ERR_NO_CIPHER: print(errCode, "No cipher file found", comment, -1, placeholderstring); break;
  case ERR_FNF: print(errCode, "File not found", comment, -1, placeholderstring); break;
  case ERR_FWRITE: print(errCode, "Unable to write to file", comment, -1, placeholderstring); break;
  case ERR_FREAD: print(errCode, "Unable to read from file", comment, -1, placeholderstring); break;
  case ERR_FOPEN: print(errCode, "Unable to find or open file", comment, -1, placeholderstring); break;

  case ERR_UNRES_SYMBOL: print(errCode, "Unable to resolve symbol", comment, -1, placeholderstring); break;
  case ERR_UNREC_CHAR: print(errCode, "Unrecognized character", comment, -1, placeholderstring); break;
  case ERR_REDEF_SYMB: print(errCode, "Multiply declared symbol", comment, -1, placeholderstring); break;

  case ERR_ILL_OP_ARG: print(errCode, "Illegal argument", comment, -1, placeholderstring); break;
  case ERR_ILL_OP: print(errCode, "Illegal operand", comment, -1, placeholderstring); break;

  case ERR_SETTING: print(errCode, "Unrecognized CNS setting", comment, -1, placeholderstring); break;
  case ERR_SETTING_VALUE: print(errCode, "Illegal value for CNS setting", comment, -1, placeholderstring); break;
  case ERR_SETTING_TYPE: print(errCode, "Illegal setting type", comment, -1, placeholderstring); break;

  case ERR_INV_TYPE: print(errCode, "Invalid type", comment, -1, placeholderstring); break;


  default:

  break;
}

printf(COLOR_RESET "\n");
}

bool isFatal()
{
  return ((numErrors > 0) || ((numWarnings > 0) && fatalWarning));
}
