#ifndef STRUCTURE
#define STRUCTURE

#include <string>

using namespace std;

//represents operational compatibility
//numerical representation of input/output types
typedef unsigned long long signature;

#define mInteger  1
#define mFloat    2
#define mTransm   3
#define mCell     4

/*
Base cell definition
Note that some fields are of a different type or missing
than in the end system. This is only to provide a frame of
reference to aid in compilation, and is not simulation ready
*/
struct baseCell
{
baseCell();
~baseCell();

unsigned id;

//fields
unsigned * targets;
unsigned * weights;

float threshold;//point of action potential. 0 sets graded potential
float equilibrium;//rate to base level

unsigned short outSignal;//transmitter type signal
unsigned short inSignal;//acceptable signal types
unsigned short tmpSignal;//stores propagating signal. Using -o will prevent this
//from being compiled if not used

//method references
//these dictate which algorithm to use for each
unsigned updateMethod;
unsigned fireMethod;
unsigned intakeMethod;

};

//User defined cell
struct cellObject : public baseCell
{
  cellObject();
  ~cellObject();

  baseCell*base;

  unsigned*customMethods;
};

struct cluster
 {
  cluster();
  ~cluster();

  unsigned id;

  unsigned * items;//list of templates
};

struct region
{
  region();
  ~region();

  unsigned id;

  cluster*items;
};

struct subSystem
{
  subSystem();
  ~subSystem();

  unsigned id;

  region*items;
};

struct method
{
  method();
  ~method();

  unsigned id;

  char**code;
  int retType;
  int*params;
};

struct component
{
  component();
  ~component();

  unsigned id;
  unsigned char type;
};

#endif
