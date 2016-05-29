#ifndef CONFIGURE
#define CONFIGURE
/*
Holds configuration data from commandline,
as well as identified information

Generated in loadCMD (Launcher.cpp)
*/

#include <string>
using namespace std;

const int _nocompile = 0;
const int _precompile = 1;
const int _tokenize = 2;
const int _lexical = 3;
const int _encode = 4;
const int _build = 5;
const int _assemble = 6;

struct Config
{
  //command line settings
  bool critWrn;//warnings are fatal
  bool debug;//print debugging information
  bool buildRTE;//build runtime enviornment
  bool buildCTM;//build connectome file
  bool staticObjects;//objects will not spawn/prune
  bool createEncodeFile;//write encode file to disk
  bool useMake;//utilize makefile
  bool optimize;//additional scans to improve performance

  string makeFile;//if blank and enabled, search locally

  //project file
  string projectName;
  string projectVersion;
  string targetLanguage;
  string srcFile;

  int maxObjects;//maximum cells/groups allowed (0=unlimited)
  int signalLength;//bytes used in signal object

  float TDF;//time dilation factor
  float GRP;//global resting potential

  bool experimental;//experimental features

  //internal
  int buildLevel;

};

#endif
