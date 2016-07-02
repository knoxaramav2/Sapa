#ifndef COMPILATION
#define COMPILATION

#include "Bytecode.h"
#include "Config.h"

#include <string>
#include <vector>

using namespace std;

struct token
{
  unsigned char meta;
  void * data;
};

//holds pre-compiled version of source files
//useful for debugging printouts
//holds additional meta information
struct dataFile
{
  vector <string> libraries;//imported libraries
  vector <string> code;//condensed code
};

dataFile preCompile(Config &);

vector <token> tokenize(Config &, dataFile &);

void lexical (Config &, dataFile &, vector <token> &);

void encode (Config &);

void assemble (Config &);

#endif
