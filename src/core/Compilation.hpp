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

};

enum lexCommand
{

};

struct lexeme
{
  string raw;
  lexData meta;

};

struct statement
{
  vector <lexeme> info;
  lexData command;
};

struct declaration
{

};

struct script
{
  string title;
  string signature;
};

//scans file for symbols
//returns symbolic signature
string scanner(Project&);

vector <lexeme> lexical(Project&);

void syntactal(Project&, vector<lexeme>&);

void semantic();


#endif
