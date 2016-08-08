#ifndef CONFIG
#define CONFIG

#include <string>

using namespace std;

struct Config{

  //Compiler settings (CLI)
  string cns;//CNS path file

  bool makefile;
  bool ctm;
  bool rte;
  bool optimize;
  bool debug;

  //Project settings (CNS)
  string projectName;
  string version;
  string language;//target language

  float tdf;//time dialation factor
  float rsp;//global default resting potential

  float nmax;
  float ntran;

  bool experimental;
  bool cdbg;
  bool cstatic;

  string sourcePath;
};

#endif
