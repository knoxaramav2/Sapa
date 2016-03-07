#ifndef REGISTRY
#define REGISTRY

/*
Defines registries for templates
*/

#include <vector>
#include <string>

using namespace std;

#include "Structures.hpp"

//stores id's by symbol hash
struct idRegistry
{
  idRegistry();
  ~idRegistry();

  unsigned*idList;
  unsigned long long hashList;
};

struct componentRegistry
{
  componentRegistry();
  ~componentRegistry();

  component*items;
};

struct methodRegistry
{
  methodRegistry();
  ~methodRegistry();

  method*items;
};

struct cellRegistry
{
  cellRegistry();
  ~cellRegistry();

cellObject*items;
};

struct clusterRegistry
{
  clusterRegistry();
  ~clusterRegistry();

  cluster*items;
};

struct regionRegistry
{
  regionRegistry();
  ~regionRegistry();

  region*items;
};

struct subsysRegistry
{
  subsysRegistry();
  ~subsysRegistry();

  subSystem*items;
};

struct fileRegistry
{
  fileRegistry();
  ~fileRegistry();

  vector <string> file;
  vector <long long unsigned> lookup;

  //return 1 if duplicate
  bool addToRegistry(string);
};

#endif
