#ifndef SAPA_STATE
#define SAPA_STATE

#include <vector>
#include <string>

using namespace std;

enum LCode{

  //logical operators
  land, lor, lnot, lnand, lnor, lxor, lxnor,
  llss, lgtr, lequ, llssequ, lgtrequ, lnotequ,
  loutex, loutinc, linex, lininc,
  //arithmetic operators
  ladd, lsub, ldivide, lmult, lmod, lpow, lroot,
  //functional operators
  lref, lindx,
  //setters
  lset, laddset, lsubset, lmultset, ldivset,
  //primitives / type keywords
  lint, lfloat, lbool, lstring, lcell, lgroup, lfnc,
  //commands
  lif, lelse, lwhile, lbreak, lgoto, lend, lnew, ldel,
  //attributes
  loverride, lfinal, labstract,
  //encaps
  lsfnc, lefnc, lsprm, leprm
};

//basic identified string
struct Word
{
  LCode code;
  string raw;
};

struct KeyPair{
  string key;
  vector <string> values;
};

//represents file-by-file pre-compilation data
struct Page{
  vector <KeyPair> alia;

  string raw;
};

#endif
