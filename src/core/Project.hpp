#ifndef PROJECT
#define PROJECT

#include <string>
#include <vector>

#include "Registry.hpp"

using namespace std;

/*
Defines project settings and constants
*/

enum buildLevel{_noBuild, _preComp, _Scanner, _Tokenize, _Compile, _Build};

class Project
{
  //location of executable
  string localAddr;
  string cnsFile;

  void fncImport(vector <string>, string);
  void fncDatSet(vector <string>, string);

public:
  //settings***************
  //compilation
  bool binaryComp;//compile to binary (must have appropriate compilers installed)
  bool mkFile;/*look for local makefile to compile against
  otherwise, use default compilation settings*/
  bool noWarn;
  bool noErr;
  bool vEW;//Error/warning volatile

  //RTE settings
  bool ddbg;//RTE prints step information (debugging mostly)
  bool cdbg;//compilation debug printouts
  bool makeCTM;
  bool makeRTE;
  unsigned transSize;

  //other
  string projName;
  vector <string> srcFiles;

  //Compilation level
  bool c_scan;
  bool c_lex;
  bool c_build;

  Registry registry;

  buildLevel bLevel;

  //establishes OS specific constants
  Project(string);
  bool loadCNS();
  bool setCNS(string);
  bool hasCNS();

  void setBuildLevel(buildLevel);

  string getLAddr();

  string formatPath(string, string);
};

#endif
