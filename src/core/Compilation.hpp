#ifndef COMPILER
#define COMPILER

//provides prototypes for lexical, syntax and semantic analysis
#include <string>
#include <vector>

using namespace;

enum lexType{
  //Raw Types
  _int, _deci, _string,
};

struct lexeme
{
  string value;
  lexType attribute;
  bool raw;//if registry check is required
}

vector <lexeme> lexical(Project&);

void syntactal(Project&, vector<lexeme>&);

void semantic();


#endif
