#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Libs/KNX_Libraries/KNX_Hash.h"
#include "Libs/KNX_Libraries/KNX_String.h"
#include "Libs/KNX_Libraries/KNX_File.h"

#include "Settings.hpp"
#include "Compiler.hpp"
#include "Registry.hpp"
#include "Structures.hpp"

using namespace std;

#define VERSION "1.0.0"

#define DEBUG false

void help()
{
  printf("\n");

  printf("-v      Print version\n");
  printf("-h      Print help dialogue\n");
  printf("-o      Enable code optimization\n");
  printf("-d      Debug mode\n");
  printf("-e      Enable evolution\n");
  printf("-w      Suppress warnings\n");
  printf("-a      Print operations\n");
  printf("-r      Produce compatible runtime engine\n");

  printf("--bitmode=(32 or 64)  Set compiler bitmode\n");
  printf("--output=directory    Set build directory\n");
  printf("--title=name          Set output name\n");
  printf("--lang=langauge       Set RTE source language. Supports C/Java");

  printf("\n");
}

string getValue(char*raw)
{
  size_t spos = string(raw).find_first_of("=",3);

  if (spos==string::npos)
    return string();

  return string(raw+spos+1);
}

string getOption(char*raw)
{
  size_t spos = string(raw).find_first_of("=",3);

  if (spos==string::npos)
    return string();

  string ret(raw);

  ret.erase(ret.begin()+spos, ret.end());
  ret.erase(ret.begin(), ret.begin()+2);

  return ret;
}

//sets compilation settings
//returns false if meant to exit
settings parseCMD(int argc, char**argv, bool&bcmp)
{

  bool fatal = false;
  bool doCompile = false;

  settings stt;

  for (int loop = 1; loop<argc; ++loop)
  {
    if (argv[loop][0]=='-')
    {
      if (strlen(argv[loop])==1)
      {
        printf("Error: option flag missing identifier\n");
        fatal=true;
      }else
      {
        if (argv[loop][1]=='-')//assignment
        {
            string value = getValue(argv[loop]);
            string option = getOption(argv[loop]);
            printf(">>%s:%s\n",option.c_str(), value.c_str());

            option=toLower((char*)option.c_str());
            //option=string(toLower(option.c_str()));
            if (option=="src")
            {
              stt.inputFile=value;
              doCompile=true;
            }

            //non setting commands
            else if (option=="depscan")//scans ctm file and identifies dependencies
            {
              //TODO
            }

            else
            {
              printf("Warning: \'%s\' unrecognized option\n", option.c_str());
            }

        }else if (strlen(argv[loop])==2)//toggle
        {
          switch(argv[loop][1])
          {
            case 'h': help(); break;
            case 'v': printf("%s\n", VERSION); break;
            case 'o': stt.optomize=true; break;
            case 'd': stt.debugMode=true; break;
            case 'e': stt.evolution=true; break;
            case 'w': stt.suppressWarnings=true; break;
            case 'a': stt.printProgress=true; break;
            case 'r': stt.produceRTE=true; break;
            case 'c': stt.produceCTM=true; break;
          }
        }else
        {
          printf("Error: Singly dashed options may only be followed by a single character identifier\n");
          fatal=true;
        }
      }
    }else
    {
      printf("Error: [%s] not expected at this time\n", argv[loop]);
      fatal=true;
    }
  }

if (fatal)
  printf("Cancelling operation\n");

bcmp = (!fatal && doCompile);

return stt;
}

#if DEBUG == 0
int main(int argc, char**argv, char**envo)
{

bool Cmp = false;
settings stt = parseCMD(argc, argv, Cmp);
if (!Cmp)
  return 0;

fileRegistry fileReg;

/*
Begin compilation procedure:

1) Read CNS file
2) Create table from imports
3) Create dependency signature
*/

//load project file
if (!loadCNS(stt,fileReg))
{
  printf("Failed to load project file\n");
  return -1;
}

return 0;
}
#endif

#if DEBUG == 1

int main(int argc, char**argv)
{
  printf("DEBUG\n");

}

#endif
