#ifndef STRUCTURE
#define STRUCTURE

#include <string>

using namespace std;

/*
Defines structures required for all steps of compilation
*/

//Cell base template

//orders of complexity/abstraction
#define UNDEF   0
#define CELL    1
#define CLUSTER 2
#define REGION  3
#define NETWORK 4
#define SYSTEM  5

//other structures
#define FIBER   10
#define EXPRS   11//expression

//Components
#define FIELD   20

//Supported C data types
#define mNone   0//should never make it passed compilation
#define mInt    1
#define mFlt    2
#define mBool   3

typedef struct __polybase
{
  unsigned type;//references object type
  size_t nameHash;//used for lookup
} object;

//defines a particular component in the object (methods, variables)
typedef struct __defField
{
  unsigned type;
  void*data;

} component;

typedef struct __cellFormat
{
object*base;

//basic fields
float volatility;
float threshold;

//implementable
component*components;//NULL terminated

} cellBase;

typedef struct __table
{

object**elements;//second pointer references array, first keeps static link to possible reallocation. NULL terminated

}hashTable;

#endif
