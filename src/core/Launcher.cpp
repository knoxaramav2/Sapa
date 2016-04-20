
#include "Error.hpp"
#include "Info.hpp"
#include "Project.hpp"

#include "Libs/KNX_Libraries/KNX_String.h"

#include <stdio.h>

using namespace std;

void help()
{

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
          case 'b': p.binaryComp=true; break;
          case 'm': p.mkFile=true; break;
          case 'c': p.makeCTM=true; break;
          case 'r': p.makeRTE=true; break;
          case 'v': vInfo(); break;
          case 'h': help(); break;
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


  return p.hasCNS();
}

int main(int argc, char**argv)
{
  Project prj("test");

  if (!loadCMD(argc,argv,prj))
    return 0;

  prj.loadCNS();

  if(prj.cdbg)
    prj.registry.printItems();

  //scan for symbols

return 0;
}
