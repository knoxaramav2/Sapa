#ifndef PROJECT
#define PROJECT

#include <string>
#include <vector>

#include "Registry.hpp"

using namespace std;

/*
Defines project settings and constants
*/

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

  //RTE settings
  bool ddbg;//RTE prints step information (debugging mostly)
  bool cdbg;//debugging features in compiled version
  bool makeCTM;
  bool makeRTE;
  unsigned transSize;

  //other
  string projName;
  vector <string> srcFiles;

  Registry registry;

  //establishes OS specific constants
  Project(string);
  bool loadCNS();
  bool setCNS(string);
  bool hasCNS();
};

#endif
