#ifndef HEADER
#define HEADER

#include <vector>
#include <string>

using namespace std;

//globals
string templatePath="../templates/";

/*
Define all external functions into single header
Define all classes and methods
*/

struct function
{
int id;
unsigned long long hId;//name hash
string name;
vector <string> srcCode;
string retType;
};


struct member
{
string type;
string name;
};


class cellTemplate
{
int id;//cell definition id
string alias;
unsigned long long hId;//alias hash

vector <function> fields;
vector <member> members;
};


class cellRegistry
{
vector <cellTemplate> templates;

public:
cellTemplate*getCell(int);//by id
cellTemplate*getCell(string);//by alias
int addCell();
};

int loadBioPlate();
int loadMaster();
int loadContainer();

bool makeNewProject();
bool deleteProject();

#endif
