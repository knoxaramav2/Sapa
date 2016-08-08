#ifndef COMPILATION
#define COMPILATION

#include "Config.h"
#include "Model.h"
#include "Error.h"
#include "Util.h"

#include <string>
#include <vector>

using namespace std;

//character checks
#define _isLetter(x) ((x>= 'A' && x<= 'Z') || (x>='a' && x <='z'))
#define _isNumber(x) (x>='0' && x<='9')
#define _isOperator(x) (!_isLetter(x) && !_isNumber(x))

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
void Tokenize(Config&, Codestruct&, vector<Page>& );


#endif
