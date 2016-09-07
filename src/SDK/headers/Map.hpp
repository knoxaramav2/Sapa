#ifndef SAPA_MAP
#define SAPA_MAP

#include <string>
#include <vector>

using namespace std;

struct DependSpace{
//included file
string dependency;
string fileName;
};

struct CodeBlock{
string name;
string code;
};

class CodeBuilder{


string headerComment;//comment to place at top of source file
string import;//import file command

vector <CodeBlock> codeBlocks;
vector <DependSpace> dependencies;

public:

};

#endif
