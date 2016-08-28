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
#define _isWhitespace(x) (x==' ' || x=='\t' || x=='\n' || x=='\r' || x==0)
#define _isQuote(x) (x=='\'' || x=='\"')
#define _isOperator(x) (((x>=1 && x<=47) || (x>=58 && x<=64) || (x>=91 && x<=96) || (x>=123)) && !_isWhitespace(x))

enum LoadState{
  _NOCOMPILE, _CNS, _PRECOMP, _TOKENIZE, _MODEL, _ASSEMBLE
};

struct Symbol{
  string raw;
  LCode type;
};

struct KeyPair{
  string key;
  vector <string> values;
};

struct Codestruct
{
  vector <KeyPair> alia;
  vector <Symbol> symbolTable;
  vector <string> sources;
  string sourceMap;
  string raw;
};

Codestruct LoadCNS(Config&);
vector <Page> Precompile(Config&, Codestruct&);
Token * Tokenize(Config&, Codestruct&, vector<Page>& );

#endif
