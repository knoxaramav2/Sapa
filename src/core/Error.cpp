#include "Error.hpp"

#include <stdio.h>
#include <string>

int errCounter=0;
int wrnCounter=0;

void printErr(int errCode, string msg, int index, string line)
{
  printf("\033[1;31mError [%d]: %s\033[0m\n", errCode, msg.c_str());
  if (line.size()>0)
    printf("\033[1;31m\t%s\033[0m\n",line.c_str());
  if (index<0)
    return;
  printf("\t");
  for (; index>0; --index)
    printf(" ");
  printf("^\n");
}

void printWrn(int errCode, string msg, int index, string line)
{
  printf("\033[1;33mError [%d]: %s\033[0m\n", errCode, msg.c_str());
  if (line.size()>0)
    printf("\t%s\n\t",line.c_str());
  if (index<0)
    return;
  for (; index>0; --index)
    printf("\033[1;33m \033[0m");
  printf("^\n");
}

void printMsg(int errCode, string msg)
{
  printf("\033[1;34mMisc Wrn/Err [%d]: %s\033[0m\n", errCode, msg.c_str());
}

void ErrorReport()
{
printf("\033[1;32m%d Errors | %d Warnings | %d Total issues\033[0m\n", errCounter, wrnCounter, errCounter+wrnCounter);
}

void postError(string line, string msg, unsigned errCode, int errIndex, char prntPolicy)
{
  //prntPolicy == (suppressErr<<1) ^ (suppressWrn)
  if (errCode<ERROR_LIM)
  {
    ++errCounter;
    if ((prntPolicy>>1) & 1)
      return;
  }else if (errCode<WARN_LIM)
  {
    ++wrnCounter;
    if ((prntPolicy>>0) & 1)
      return;
  }else
  {
    printMsg(errCode, line);
  }

  switch(errCode)
  {
    //Errors
    case ERR_NO_SRC: printErr(errCode, "No source file specified", -1, ""); break;
    case ERR_MSS_CMD_PARAM: printErr(errCode, "Argument requires parameter", -1, msg); break;
    case ERR_INV_OPT: printErr(errCode, "Invalid command line argument", -1, line + ' ' + msg); break;

    case ERR_NO_LANG: printErr(errCode, "No source language specified in CNS file", -1, ""); break;
    case ERR_INV_CMD: printErr(errCode, "Invalid CNS setting", -1, line); break;
    case ERR_CNS_404: printErr(errCode, "Unable to open CNS file", -1, msg); break;
    case ERR_EXPCT_COM: printErr(errCode, "Expected statement", errIndex, line); break;
    case ERR_EXPCT_ARG: printErr(errCode, "Expected argument", errIndex, line); break;
    case ERR_INV_CNS_ARG: printErr(errCode, "Invalid CNS argument", errIndex, line); break;
    case ERR_SETTING_REDEF: printErr(errCode, "Mutliple CNS setting values for " + msg, errIndex, line); break;
    case ERR_MULT_COM: printErr(errCode, "Multiple commands on CNS line", errIndex, line); break;
    case ERR_NO_COM: printErr(errCode, "No command found", errIndex, line); break;
    case ERR_ARG_BFR_COM: printErr(errCode, "Argument before command", errIndex, line); break;

    case ERR_REG_NCMP_TYPE: printErr(errCode, "Incompatible registry entry", errIndex, line); break;
    case ERR_RES_ENTRY: printErr(errCode, "Illegal reserved registry access", errIndex, line); break;
    case ERR_REG_NOT_FOUND: printErr(errCode, "Symbol not found : " + msg, errIndex, line); break;

    case ERR_IMRT_NOT_FOUND: printErr(errCode, "Import not found " + msg, errIndex, line); break;

    //Warnings
    case WRN_UNBOUND_QUOTE: printWrn(errCode, "Unclosed string", errIndex, line); break;
  }
}

bool isFatal(bool isVol)
{
  return ((bool)errCounter || ((bool)wrnCounter && isVol));
}
