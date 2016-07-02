#include <stdio.h>

#include "Error.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern bool suppressError;
extern bool suppressWarning;
extern bool fatalWarning;
extern unsigned numWarnings;
extern unsigned numErrors;

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

  string color = ANSI_COLOR_WHITE;
  string codeSeg;
  codeSeg.insert(codeSeg.begin(), code.begin()+lindex, code.begin()+rindex);

  if (ecode <= MAX_WARNC)
    color = ANSI_COLOR_YELLOW;
  else if (ecode <= MAX_ERRC)
    color = ANSI_COLOR_RED;

  printf("%s%s%s\n", color.c_str(), message.c_str(), ANSI_COLOR_RESET);
  printf("\t%s\n", codeSeg.c_str());
  for (unsigned x=lindex; x<rindex; ++x) printf(" ");
  printf("^\n");
  printf("%s\n", comment.c_str());

}

void postError (unsigned errCode, int index, string&code, string comment)
{
if (errCode >= MIN_WARNC && errCode <= MAX_WARNC)
{
  ++numWarnings;
  if (suppressWarning)
    return;
}else if (errCode >= MIN_ERRC && errCode <= MAX_ERRC)
{
  ++numErrors;
  if (suppressError)
    return;
}else{
  return;
}

switch (errCode)
{
  //Warnings


  //Errors

  default:
  break;
}

}

bool isFatal()
{
  return ((numErrors > 0) || ((numWarnings > 0) && fatalWarning));
}
