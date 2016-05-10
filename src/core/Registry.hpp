#ifndef REGISTRY
#define REGISTRY

/*
Defines searchable table for all symbols and fields
*/

#include "Bio.hpp"

#include <string>
#include <vector>

using namespace std;

enum regType{
  //data type
  _NA,
  _bool, _numeric, _string,
  _list, _psuedo,
  _cell, _group

};

struct RegItem
{
  unsigned long long hash;
  string raw;
  regType type;
  bool reserved:1;//immutable if true
  bool toggle;//general purpose toggle
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
  bool toggleItem(string);
  bool setItem(string);
  bool unsetItem(string);

  regType getType(string);
  RegItem * getItem(string);
  vector <RegItem *> getAllOfType(regType);

  //update existing registry
  //entry name, data pointer, regType, res access, replace (true)/append(false)(only for list)
  bool update(string, void*, regType, bool, bool);
};

#endif
