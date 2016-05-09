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
_lNa, _lSymbol,
//command
_lDcell, _lDGroup, _lDLink, _lDTrans,
_lDEnd,
//types
_lString, _lInt, _lFloat, _lVoid, _lproc, _lChar,

//operators
//math
_lAdd, _lSub, _lMult, _lDiv, _lMod, _lRoot, _lPow,
//assignment
_lSet, _lAddSet, _lSubSet, _lMultSet, _lDivSet,
//comp logic
_lGtr, _lLss, _lEqu, _lNEqu, _lGtrEqu, _lLssEqu, _lOutRange, _lInRange,
//conv logic
_lAnd, _lNand, _lOr, _lNor, _lXNor, _lXOr, _lNot,
//collec
_lBodyOpen, _lBodyClose, _lArgOpen, _lArgClose, _lListOpen, _lListClose, _lIndex, _lNItem,
//misc
_lRef, _lInc, _lDec, _lEnd
};

#define isDelim(x) ((x<'a' || x>'z') && (x<'A' || x>'Z') && (x<'0' || x>'9') && x!='_')
#define isWhitespace(x) (x==' ' || x=='\t' || x=='\n')
#define isNumber(x) (x>='0' &&  x<='9')
#define isQuote(x) (x=='\'' || x=='\"')
#define isMath(x) (x=='+' || x=='-' || x=='*' || x=='/' || x=='%' || x=='^' || x==(char)251)
#define isComparison(x) (x=='<' || x=='>' || x=='=')
#define isLogic(x) (x=='&' || x=='!' || x=='|')
#define isGroup(x) (x=='[' || x==']' || x=='{' || x=='}' || x=='(' || x==')')
#define isReference(x) (x==':' || x=='.' || x==',')
#define isCompound(x) ((isMath(x) || isComparison(x) || isLogic(x)) && (x!=(char)251 && x!='^'))

struct lexeme
{
  string raw;
  lexData meta;

  lexeme();
  lexeme(string, lexData);
};

struct rawscript
{
  string file;
  string code;
};

//scans file for symbols
//returns symbolic signature
string scanner(Project&);

vector <lexeme> lexical(Project&, string&);

void syntactal(Project&, vector<lexeme>&);

void semantic();

//line to parse, true=search for symbols
vector <lexeme> lexSplit(string, bool);

string preProcessor(Project&);

#endif
