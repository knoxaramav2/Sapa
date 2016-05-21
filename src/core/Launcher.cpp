

#include "Libs/KNX_Libraries/KNX_String.h"

#include <stdio.h>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

using namespace std;

void help()
{
  printf("\n\n");
  printf("-d           Enable debug printouts\n");
  printf("-w           Suppress warnings\n");
  printf("-e           Suppress errors\n");
  printf("-a           Fail compilation on warning or error\n");
  printf("-b           Enables full compilation\n");
  printf("-m           Sets makefile for RTE compilation\n\
  Implicitly enables RTE build\n");
  printf("-c           Enable connectome build\n");
  printf("-r           Enable runtime enviornment build\n");
  printf("-v           Print version information\n");
  printf("-p           Enable Precompiler\n");
  printf("-h           Print this dialogue\n\n");
  printf("-l           Use Sapa local project directory instead of caller path\n");
}

void vInfo()
{
  string OS;
  #ifdef __WINDOWS
  OS="Windows";
  #elif defined __LINUX
  OS="Linux";
  #else
  OS="Unrecognized OS";
  #endif
  printf("version :%s %d-bit <%s>\n", VERSION, BITMODE, OS.c_str());
}

//load command line options
bool loadCMD(int argc, char**argv)
{
  

  return false;
}

int main(int argc, char**argv)
{
  if (!loadCMD(argc,argv))
    return 0;

return 0;
}
