

#include "Libs/KNX_Libraries/KNX_String.h"
#include "Libs/KNX_Libraries/KNX_File.h"

#include "Database.h"
#include "Error.h"
#include "Config.h"
#include "Compilation.h"
#include "Util.h"

#include <stdio.h>
#include <string.h>
#include <chrono>
#include <string>
#include <vector>

#define DEVMODE false

int buildLevel = 0;

using namespace std;

void help()
{

  printf("\n\n");
  printf("-d           Enable debug mode\n");
  printf("-m           Use makefile\n");
  printf("-c           Generate connectome file\n");
  printf("-r           Generate simulation enviornment\n");
  printf("-w           Suppress warning outputs\n");
  printf("-e           Suppress error outputs\n");
  printf("-f           Warnings fatal\n");
  printf("-v           Print version info\n");
  printf("-s           Print symbolic signature\n");
  printf("-h           Print this dialogue\n");
  printf("-o           Enable optimizations\n");

  printf("--src        Set CNS file path\n");
  printf("--lang       Set language to compile to\n");
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
  printf("Version: %s %d-bit <%s> Encoder: %d\n", VERSION, BITMODE, OS.c_str(), 1);
}

//set build level to highest of the two inputs
inline void setBuildLevel(int newLevel)
{
  buildLevel = newLevel > buildLevel? newLevel : buildLevel;
}

bool validateExpected(int x, int argc, char**argv)
{
  if (x+1 < argc && argv[x+1][0]!='-'){
    return true;
  }else{
    printf("Argument for %s expected\n", argv[x]);
    ++numErrors;
    return false;
  }
}

Config parseCmd(int argc, char ** argv)
{
  Config config;

  config.tdf=1.0f;
  config.debug=false;
  config.cdbg=false;
  config.makefile=false;
  config.ctm=false;
  config.rte=false;
  config.optimize=false;
  config.experimental=false;
  config.tdf=1.0f;
  config.rsp=-70.0f;
  config.nmax=500;
  config.ntran=2;
  config.cdbg=false;
  config.cstatic=false;

  for (int x = 1; x < argc; ++x)
  {
    if (argv[x][0]!='-')
    {
      printf("Option %s must start with \'-\'\n", argv[x]);
      ++numErrors;
      continue;
    }

    size_t len = strlen(argv[x]);

    if (len == 2)
    {
      switch(argv[x][1])
      {
        case 'd': config.debug=true; break;
        case 'm': config.makefile=true; setBuildLevel(_BUILD); break;
        case 'c': config.ctm=true; setBuildLevel(_BUILD); break;
        case 'r': config.rte=true; setBuildLevel(_BUILD); break;
        case 'w': suppressWarning=true; break;
        case 'e': suppressError=true; break;
        case 'f': fatalWarning=true; break;
        case 'v': vInfo(); break;
        case 's': printf("---\n"); break;
        case 'h': help(); break;
        case 'o': config.optimize=true; break;
        default:
        printf("Unrecognized option \'%c\'\n", argv[x][1]);
        continue;
      }
    }else if (len > 2)
    {
      if (strncmp(argv[x], "--src", 5) == 0 && validateExpected(x, argc, argv))
      {
          ++x;
          string extension = getExtension(argv[x]);

          config.cns= string(getFileName(argv[x])) + (extension.empty() ? "" : "."+extension);
          config.sourcePath = getPath(argv[x]);

          setBuildLevel(_TOKENIZE);
      }
      else if (strncmp(argv[x], "--lang", 6) == 0 && validateExpected(x, argc, argv))
      {
          config.language=argv[++x];
      }else{
        printf("Unrecognized option: %s\n", argv[x]);
        ++numErrors;
        continue;
      }
    }else{
      printf("Option tag missing identifier\n");
      ++numErrors;
      continue;
    }
  }

  return config;
}

#if DEVMODE == false

int main(int argc, char**argv)
{
  Config config = parseCmd(argc, argv);

  Codestruct codestruct;
  vector <Page> pages;
  Token * stream;

  if (buildLevel >= _CNS)
    {codestruct = LoadCNS(config);}
  if (buildLevel >= _PRECOMP)
    {pages = Precompile(config, codestruct);}
  if (buildLevel >= _TOKENIZE)
    {stream = Tokenize(config, codestruct, pages);}
  if (buildLevel >= _COMPILE)
    {Compile(stream, config, codestruct);}

  if (isFatal() == false)
    printf("\nCompilation complete\n");
  else
    printf("\nCompilation failed\n");

  printf("%u Warnings | %u Errors\n", numWarnings, numErrors);

return 0;
}

#else

int main(int argc, char**argv)
{
  enum {_s1=0, _s2, _s3};
  int state = _s1;

  printf("%d\n", bitAction(state, _s1, _bmSet));
  printf("%d\n", bitAction(state, _s1, _bmCheck));
  printf("%d\n", state);

  printf("%d\n", bitAction(state, _s3, _bmSet));
  printf("%d\n", bitAction(state, _s3, _bmCheck));
  printf("%d\n", state);

  printf("%d\n", bitAction(state, _s2, _bmCheck));
  printf("%d\n", bitAction(state, _s2, _bmSet));
  printf("%d\n", bitAction(state, _s2, _bmCheck));
  printf("%d\n", state);

  printf("%d\n", bitAction(state, _s1, _bmClear));
  printf("%d\n", bitAction(state, _s1, _bmCheck));
  printf("%d\n", state);


  return 0;
}

#endif
