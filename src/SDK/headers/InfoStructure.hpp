#ifndef SAPA_INFO_STRUCT
#define SAPA_INFO_STRUCT

#include <string>
#include <vector>

using namespace std;

enum LCode{
  //meta
  lMeta=0,
  lnan,
  //logical operators
  lLogicOperator=100,
  land, lor, lnot, lnand, lnor, lxor, lxnor,
  llss, lgtr, lequ, llssequ, lgtrequ, lnotequ,
  loutex, loutinc, linex, lininc,
  //arithmetic operators
  lMathOperator=200,
  ladd, lsub, ldivide, lmult, lmod, lpow, lroot,
  //functional operators
  lFuncOperator=300,
  lref, lindx, lstop, llist,
  //setters
  lSetOperator=400,
  lset, laddset, lsubset, lmultset, ldivset, linc, ldec,
  landset, lorset, lnotset,
  //primitives / type keywords
  lType=500,
  lint, lfloat, lbool, lstring, lchar,//primitives
  lBodyType=550,
  lcell, lgroup, lfnc, larray, lsignal, lobj,//body types
  //macros
  lMacro=600,
  ltrue, lfalse,
  //commands
  lComm=700,
  lif, lelse, lwhile, lbreak, lgoto, lend, lnew, ldel, lfor,
  //attributes
  lAttr=800,
  loverride, lfinal, labstract, lrequired,
  //encaps
  lEncap=900,
  lsfnc, lefnc, lsprm, leprm, lsbrk, lebrk,
  //organization
  lOrg=1000,
  lnamespace,
  //system
  lSystem=1100,
  lpstart, lpend, lsym, lcall, ldef,
  //id reserved
  lReserved=1200,
  lobjid
};

inline bool isOperator(int c) {return c>lLogicOperator && c<lSetOperator+100;}
inline bool isType(int c){return c>lType && c<lType+100;}
inline bool isSymbol(int c){return c==lsym || c>lReserved;}
inline bool isMacro(int c){return c>lMacro && c<lMacro+100;}
inline bool isKeyword(int c){return c>lComm && c<lComm+100;}
inline bool isAttr(int c){return c>lAttr && c<lAttr+100;}
inline bool isSCap(int c){return (c>lEncap && c<lEncap+100) && ((c-lEncap)%2!=0);}
inline bool isECap(int c){return (c>lEncap && c<lEncap+100) && ((c-lEncap)%2==0);}
inline bool isOrg(int c){return c>lOrg && c<lOrg+100;}
inline bool isSys(int c){return c>lSystem && c<lSystem+100;}


enum AttrCode{
  arequired
};

struct Token{
  string raw;
  LCode type;
  Token * previous;
  Token * next;
};

struct Attribute{
  int id;
  string value;

  Attribute(int, string);
};

struct Argument{
  string type;
  string title;
};

struct OBase{
  OBase(string, LCode);

  OBase * parent;

  string title;
  vector <Attribute> attributes;
  LCode type;
  int id;
};

typedef OBase Member;

struct Function : public OBase{
  vector <Argument> arguments;
  Token * stream;

  Function(string, LCode);
};

class Object : public OBase{
  vector <Member> members;
  vector <Function> functions;
  vector <Attribute> attributes;
  string baseNamespace;

public:
  Object(string, LCode);
};

class Namespace : public OBase{
  vector <Object> objects;
  Object * target;

public:
  Namespace(string);

};

//stores information from the compiler and allows reading of processed data
class SContext{
  Object * currentObject;
  vector <OBase *> namespaces;
public:

  SContext();

  //registers and/or selects namespace
  bool registerNamespace(string title);
  //creates and/or selects new object in current namespace
  //progressively builds model
  //closing an object will select the parent
  bool registerObject(OBase*object, Token*attributes);
  //closes current object and adds it to model
  bool finalizeObject();
  //closes current namespace
  //update current object
  //return false if no active object or if input is invalid
  bool updateObject();
  //verify model closes out
  bool closeModel();
  //return type of current object
  LCode getCurrentType();
};

#endif
