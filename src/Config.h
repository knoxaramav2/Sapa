#ifndef CONFIGURE
#define CONFIGURE
/*
Holds configuration data from commandline,
as well as identified information

Generated in loadCMD (Launcher.cpp)
*/

struct Config
{
  //command line settings
  bool noErr;//suppress error messages
  bool noWrn;//suppress warning messages
  bool critWrn;//warnings are fatal
  bool debug;//print debugging information
  bool buildRTE;//build runtime enviornment
  bool buildCTM;//build connectome file

  //project file
  string projectName;
  string projectVersion;
  string targetLanguage;

  int maxObjects;//maximum cells/groups allowed
  int staticObjects;//objects will not spawn/prune
  int signalLength;//bytes used in signal object

  float TDF;//time dilation factor
  float GRP;//global resting potential

  bool experimental;//experimental features
  bool useMake;//utilize local makefile

};

#endif
