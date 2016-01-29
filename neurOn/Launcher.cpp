#include <string>
#include <string.h>
#include <vector>
#include <fstream>

#include "Collections.h"

using namespace std;

#define VERSION "1.0.0 A"

void help()
{
  printf("-c [list.neuron]     Compile .neuron files to .ctm\n");
  printf("-l [list.ctm]        Compile .ctm files to .C and produce an executable\n");
  printf("-h                   Print this message\n");
  printf("-v                   Print compiler version\n");
  printf("-d                   Activate debug mode\n");
  printf("-o [name]            Set output file name\n");

  printf("\n\n");
}

project parseCMD(int argc, char**argv)
{

bool fatal=false;
int readMode=0;
project prj;

for (int x=1; x<argc; ++x)
{

  if (strlen(argv[x])>1)
  {
    if (argv[x][0]=='-')
    {
      switch(argv[x][1])
      {
        case 'h': help(); break;
        case 'v': printf("%s\n", VERSION); break;
        case 'c': prj.opts.doCompile=true; readMode=readMode<2?1:2;break;//will expect .C files
        case 'l': prj.opts.doLink=true; readMode=2; break;//will expect .C OR .ctm files
        case 'd': prj.opts.debugMode=true; break;
        case 'p': prj.opts.prsvC=true; break;
      }
    }else
      {
        if (readMode>0)
          prj.src.addEntry(argv[x]);
        else
          printf("Warning: Input \"%s\" ignored\n", argv[x]);
      }
  }else
    printf("Warning: Input \"%s\" ignored\n", argv[x]);
}

return prj;
}

int main(int argc, char**argv)
{
  project p = parseCMD(argc,argv);

  while (!p.src.isEmpty())
  {
    printf("%s\n", p.src.popEntry().c_str());
  }

  return 0;
}

/*
General procedure:
1: Get inputs, establish compilation level, make source lists
2a: If -c flag set, assume file type to be .neuron
2b: If -l flag set, assume file types to be .ctm
3a: Compile .neuron to .ctm (connectome) file
3b: Compile .ctm file to .c file
4: Use gcc to compile to exe

*/
