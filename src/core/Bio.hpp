#ifndef BIO
#define BIO

/*
Defines cell and group base classes
*/

#include <string>
#include <vector>

using namespace std;

struct object
{
bool isCell;

unsigned long long hash;
string name;

//3D coordinates
float x=0;
float y=0;
float z=0;

bool protect;
bool overriden;

//holds all variable declarations and methods in encoded form
string data;
};

struct cell : public object
{

};

struct group : public object
{
  bool isCellGroup;//true if cell cluster, false if group cluster
  vector <object*> items;
};

#endif
