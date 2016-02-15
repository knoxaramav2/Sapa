#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Libs/KNX_Libraries/KNX_Hash.h"

using namespace std;

#define VERSION "1.0.0"

void help()
{
  printf("\n");

  printf("-v      Print version\n");
  printf("-h      Print help dialogue\n");
  printf("-o      Enable code optimization\n");
  printf("-d      Debug mode\n");
  printf("-e      Enable evolution\n");
  printf("-w      Suppress warnings\n");
  printf("-s      Preserve C code\n");
  printf("-c      Compile to object and C files\n");

  printf("--bitmode=(32 or 64)  Set compiler bitmode\n");
  printf("--output=directory    Set build directory\n");
  printf("--title=name          Set output name\n");

  printf("\n");
}

//sets compilation settings
//returns false if meant to exit
bool parseCMD(int argc, char**argv)
{


return true;
}

int main(int argc, char**argv, char**envo)
{

if (!parseCMD(argc, argv))
  exit(0);

//printf("%llu\n",FNV_1a("Test"));
printf("%llu\n",FNV_1a("asdas"));


/*
Begin compilation procedure:

1) Generate
*/

return 0;
}
