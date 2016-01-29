#ifndef COLLECTION
#define COLLECTION

#include <string>
#include <vector>

using namespace std;

class SourceRegistry
{
vector <string> list;
public:
void addEntry(string);//add to end of list
string popEntry();//get last entry and remove it
string getEntry();//get last entry and preserve it
void clearList();//clear file list
bool isEmpty();
};

union settings
{
  struct
  {
    bool doCompile : 1;
    bool doLink : 1;
    bool debugMode : 1;
    bool prsvC : 1;//preserve C code
  };
};

struct srcFile
{
  string fileName;

  vector <string> code;
};

//defines lexic token definition
enum tokenType{
//data types
_dInt, _dFlt, _dStr,
//operator

//logic

//actuation

};



struct byteCode
{

byteCode*parent;
byteCode*success;
byteCode*failure;
byteCode**parameters;

};

class bytecodeTree
{
byteCode**roots;//roots
}

class project
{

srcFile nSrc;
srcFile cSrc;

string outputName;
public:
  settings opts;
  SourceRegistry src;

};

#endif
