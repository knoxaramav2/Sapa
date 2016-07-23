#ifndef COMPILATION
#define COMPILATION

#include "Config.h"
#include "Model.h"
#include "Error.h"

#include <string>
#include <vector>

using namespace std;

enum LoadState{
  _NOCOMPILE, _CNS, _PRECOMP, _TOKENIZE, _MODEL, _ASSEMBLE
};

struct Codestruct
{
  vector <string> sources;

  string sourceMap;
  string raw;
};

Codestruct LoadCNS(Config&);
vector <Page> Precompile(Config&, Codestruct&);


#endif
