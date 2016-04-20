#ifndef REGISTRY
#define REGISTRY

/*
Defines searchable table for all symbols and fields
*/

#include <string>
#include <vector>

using namespace std;

enum regType{
  //data type
  _NA,
  _bool, _numeric, _string,
  _list

};

struct RegItem
{
  unsigned long long hash;
  string raw;
  regType type;
  bool reserved:1;//immutable if true
  void*info;
};

class Registry
{
  vector <RegItem> listing;

public:

  Registry();

  bool addItem(string, bool, regType);
  void printItems();
  bool hasEntry(string);

  regType getType(string);

  //update existing registry
  //entry name, data pointer, regType, res access, replace (true)/append(false)(only for list)
  bool update(string, void*, regType, bool, bool);
};

#endif
