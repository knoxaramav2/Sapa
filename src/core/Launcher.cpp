

#include "Libs/KNX_Libraries/KNX_String.h"

#include "Config.h"
#include "Bytecode.h"
#include "Error.h"

#include <stdio.h>
#include <string.h>
#include <chrono>
#include <string>
#include <vector>

bool suppressError;
bool suppressWarning;
bool fatalWarning;
unsigned numWarnings;
unsigned numErrors;

using namespace std;

void help()
{

  printf("\n\n");
  printf("-d           Enable debug mode\n");
  printf("-b           Enable build\n");
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
}

void initialize()
{
  suppressError = false;
  suppressWarning = false;
  fatalWarning = false;
  numWarnings = 0;
  numErrors = 0;
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
  printf("Version: %s %d-bit <%s> Encoder: %d\n", VERSION, BITMODE, OS.c_str(), BYTECODE_VERSION);
}

//set build level to highest of the two inputs
inline int setBuildLevel(int buildLevel, int newLevel)
{
  return newLevel > buildLevel? newLevel : buildLevel;
}

//return number of arguments after given index
int getNumParams(int argc, char**argv, int x)
{
  if (x+1==argc)
    return 0;

  int y=x+1;
  for (; y<argc; ++y)
    if (argv[y][0]=='-')
      {
        --y;
        break;
      }

  return y-x;
}

void cmdErr(string argv, string message, bool&fatal)
{
  fatal=true;
  printf("%s\n\t>> %s\n", message.c_str(), argv.c_str());
}

//load command line options
Config loadCMD(int argc, char**argv)
{
  Config config;

  //initialise config object
  fatalWarning = false;

  config.debug = false;
  config.prjDebug = false;
  config.buildRTE = false;
  config.buildCTM = false;
  config.staticObjects = false;
  config.createEncodeFile = false;
  config.useMake = false;
  config.optimize = false;

  config.maxObjects = 0;
  config.signalLength = 1;

  config.TDF = 1.0f;
  config.GRP = -70.0f;

  config.experimental = false;
  config.useMake = false;

  config.buildLevel = 0;

  //begin parsing command line arguments
  bool canContinue=false;
  bool error=false;

  for (int x=1; x<argc; ++x)
  {
    if (argv[x][0]!='-' || strlen(argv[x])==1)
    {
      printf("Expected option : (%s)\n", argv[x]);
      error = false;
      break;
    }
    //single option switch (-x)
    if (strlen(argv[x])==2)
    {
      switch(argv[x][1])
      {
        case 'd': config.debug=true; break;
        case 'b': setBuildLevel(config.buildLevel, 4); break;
        case 'm': config.useMake = true; setBuildLevel(config.buildLevel, 4); break;
        case 'c': config.buildCTM = true; setBuildLevel(config.buildLevel, 4); break;
        case 'r': config.buildRTE = true; setBuildLevel(config.buildLevel, 4); break;
        case 'i': config.createEncodeFile=true; break;
        case 'w': suppressWarning = true; break;
        case 'e': suppressError = true; break;
        case 'f': fatalWarning = true; break;
        case 'v': vInfo(); break;
        case 's': break;//TODO implement this
        case 'h': help(); break;
        case 'o': config.optimize = true; break;
        default:
          printf("Unrecognized option\n");
          error = true;
        break;
      }
    }else
    {
      if (argv[x][1]!='-')
        cmdErr(argv[x], "Complex option must be prefixed with \'--\'", error);
      //complex options (--option arg...)
      else if (strcmp(argv[x], "--make")==0)
      {
          config.makeFile = argv[x];
      }
      else if (strcmp(argv[x], "--src") == 0)
      {
          int numParams = getNumParams(argc, argv, x);
          if (numParams != 1)
              cmdErr(argv[x], "Must have an argument", error);
          else
          {
            config.srcFile = argv[(x+=numParams)];
            canContinue = true;
          }

      }
      else
      {
          cmdErr(argv[x], "Option not recognized", error);
      }
    }
  }

  if (error || !canContinue)
    config.buildLevel = 0;

  return config;
}

int main(int argc, char**argv)
{
  initialize();

  Config config = loadCMD(argc, argv);

  if (config.buildLevel == _nocompile)
  {
    printf("Compilation ended\n");
    return 0;
  }
  if (config.buildLevel >= _precompile)
  {

  }
  if (config.buildLevel >= _tokenize)
  {

  }
  if (config.buildLevel >= _lexical)
  {

  }
  if (config.buildLevel >= _encode)
  {

  }
  if (config.buildLevel >= _build)
  {

  }
  if (config.buildLevel == _assemble)
  {

  }

  if (isFatal() == false)
    printf("Compilation complete\n");
  else
    printf("Compilation failed\n");

  printf("%u Warnings | %u Errors\n", numWarnings, numErrors);

return 0;
}
