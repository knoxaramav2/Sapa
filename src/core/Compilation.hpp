#ifndef COMPILER
#define COMPILER

//provides prototypes for lexical, syntax and semantic analysis
#include <string>
#include <vector>

#include "Project.hpp"

using namespace std;

//used for type and mathematical
enum lexData
{
//command
_lDcell, _lDGroup, _lDInt, _lDDec, _lDVoid, _lDproc, _lDLink, _lDTrans,
_lDEnd
//types

//operators
};

#define isDelim(x) ((x<'a' || x>'z') && (x<'A' || x>'Z'))


struct lexeme
{
  string raw;
  lexData meta;
};

struct rawscript
{
  string file;
  string code;
};

//scans file for symbols
//returns symbolic signature
string scanner(Project&);

vector <lexeme> lexical(Project&);

void syntactal(Project&, vector<lexeme>&);

void semantic();

//line to parse, true=search for symbols
vector <lexeme> lexSplit(string, bool);

string preProcessor(Project&);

#endif
