#ifndef SAPA_STATE
#define SAPA_STATE

#include <vector>
#include <string>

using namespace std;

enum LCode{
  //meta
  lnan=0,
  //logical operators
  land=10, lor, lnot, lnand, lnor, lxor, lxnor,
  llss=20, lgtr, lequ, llssequ, lgtrequ, lnotequ,
  loutex=30, loutinc, linex, lininc,
  //arithmetic operators
  ladd=40, lsub, ldivide, lmult, lmod, lpow, lroot,
  //functional operators
  lref=50, lindx, lstop, llist,
  //setters
  lset=60, laddset, lsubset, lmultset, ldivset, linc, ldec,
  landset, lorset, lnotset,
  //primitives / type keywords
  lint=80, lfloat, lbool, lstring, lchar, lcell, lgroup, lfnc, larray, lsignal,
  //macros
  ltrue=90, lfalse,
  //commands
  lif=100, lelse, lwhile, lbreak, lgoto, lend, lnew, ldel, lfor,
  //attributes
  loverride=120, lfinal, labstract,
  //encaps
  lsfnc=130, lefnc, lsprm, leprm, lsbrk, lebrk,
  //system
  lpstart=140, lpend, lsym
};

//represents file-by-file pre-compilation data
struct Page{
  string raw;
};

struct Token{
  string raw;
  LCode type;
  Token * previous;
  Token * next;
};

struct Object{
  string raw;
  Object * parent;
};

#endif
