
#include "Error.hpp"
#include "Info.hpp"
#include "Project.hpp"
#include "Compilation.hpp"

#include "Libs/KNX_Libraries/KNX_String.h"

#include <stdio.h>
#include <chrono>

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

bool loadCMD(int argc, char**argv, Project&p)
{
  for (int x=1; x<argc; ++x)
  {
    size_t argLen = strlen(argv[x]);

    if (argLen<2)
    {
      postError(argv[x], "", ERR_INV_CMD, -1, 0);
    }
    if (argLen==2)//toggle options
    {
      if (argv[x][0]!='-')
      {
        postError(argv[x], "", ERR_INV_CMD, -1, 0);
      }else
      {
        switch(argv[x][1])
        {
          case 'd': p.cdbg=true; break;
          case 'w': p.noWarn=true; break;
          case 'e': p.noErr=true; break;
          case 'a': p.vEW=true; break;
          case 'b': p.binaryComp=true; p.setBuildLevel(_Build); break;
          case 'm': p.mkFile=true; p.setBuildLevel(_Build); break;
          case 'c': p.makeCTM=true; p.setBuildLevel(_Compile); break;
          case 'r': p.makeRTE=true; p.setBuildLevel(_Compile); break;
          case 'v': vInfo(); break;
          case 'p': p.setBuildLevel(_preComp); break;
          case 'h': help(); break;
          case 'l': p.useLclDir=true; break;
          default:
          postError(argv[x], "", ERR_INV_CMD, -1, 0);
        }
      }
    }else//field settings
    {
      if (argv[x][0]!='-' || argv[x][1]!='-')
      {
        postError(argv[x], "", ERR_INV_CMD, -1, 0);
      }else
      {
        if (strncmp(argv[x], "--nowarn", 255)==0)
          p.noWarn=true;
        else if (strncmp(argv[x], "--noerr", 255)==0)
          p.noErr=true;
        else if (strncmp(argv[x], "--src", 255)==0)
          {
            if (x+1==argc)
              postError(argv[x], "", ERR_MSS_CMD_PARAM, -1, 0);
            else
            {
              p.setCNS(argv[++x]);
            }
          }
        else
          {
            postError(argv[x], "", ERR_INV_CMD, -1, 0);
          }
      }
    }
  }


  return p.hasCNS() || p.bLevel!=_noBuild;
}

int main(int argc, char**argv)
{
  Project prj("test");

  if (!loadCMD(argc,argv,prj))
    return 0;

  prj.loadCNS();

  if (prj.cdbg)
    printf("Compilation mode (%d)\n", prj.bLevel);

  //scan for symbols
  string rCode;
  if (prj.bLevel>=_preComp && !isFatal(prj.vEW))
    rCode=preProcessor(prj);
  if (prj.bLevel>=_Lexical && !isFatal(prj.vEW))
    lexical(prj, rCode);

  if(prj.cdbg)
    prj.registry.printItems();

  ErrorReport();

  if (!isFatal(prj.vEW))
  {
    printf("Compilation complete\n");
  }

return 0;
}
