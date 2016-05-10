#include "Compilation.hpp"
#include "Error.hpp"

enum readmode{rNA, rNum, rLogic, rSymbol, rString, rChar};

lexeme::lexeme()
{
  meta=_lNa;
}

lexeme::lexeme(string rstr, lexData ld)
{
  meta=ld;
  raw=rstr;
}

void formatError(string&str, size_t x, int errc, Project&prj)
{
  if (x<0 || x>str.size())
    return;

  size_t r=x;
  size_t l=x;
  while (str[l]!='\n' && l!=0) --l;
  while (str[r]!='\n' && str[r]!='\0') ++r;
  string fstr(str.begin()+l, str.begin()+r+1);
  postError(fstr, "", errc, x-l, prj.noErr<<1|prj.noWarn);
}

lexeme getOperator(char l, char r, bool&compound)
{
  lexData lxd=_lNa;
  compound=true;
  switch(l)
  {
    case '+':
    if (r=='=') lxd=_lAddSet;
    else if (r=='+') lxd=_lInc;
    else {lxd=_lAdd; compound=false;}
    break;
    case '-':
    if (r=='=') lxd=_lSubSet;
    else if (r=='-') lxd=_lDec;
    else {lxd = _lSub; compound=false;}
    break;
    case '*':
    if (r=='=') lxd=_lMultSet;
    else {lxd=_lMult; compound=false;}
    break;
    case '/':
    if (r=='=') lxd=_lDivSet;
    else {lxd=_lDiv; compound=false;}
    break;
    case '=':
    if (r=='=') lxd=_lEqu;
    else {lxd=_lSet; compound=false;}
    break;
    case '!':
    if (r=='=') lxd=_lNEqu;
    else if (r=='&') lxd=_lNand;
    else if (r=='|') lxd=_lNor;
    else {lxd=_lNot; compound=false;}
    break;
    case '&':
    lxd=_lAnd;
    compound=false;
    break;
    case '|':
    if (r=='!') lxd=_lXNor;
    else if (r=='|') lxd=_lXOr;
    else {lxd=_lOr; compound=false;}
    break;
    case '<':
    if (r=='=') lxd=_lLssEqu;
    else if (r=='>') lxd=_lOutRange;
    else {lxd=_lLss; compound=false;}
    break;
    case '>':
    if (r=='=') lxd=_lGtrEqu;
    else if (r=='<') lxd=_lInRange;
    else {lxd=_lGtr; compound=false;}
    break;
  }
  if (lxd==_lNa)
    printf("\n\t\tSystem Error: Invalid lexical operator\n");
  return lexeme("", lxd);
}

lexeme getSym(string&str, size_t l, size_t r, Project&prj)
{
  lexData lxd=_lNa;
  string substr(str.begin()+l, str.begin()+r);

  if (substr=="new") lxd=_kwNew;
  else if (substr=="override") lxd=_kwOverride;
  else if (substr=="delete") lxd=_kwDelete;
  else if (substr=="loop") lxd=_kwLoop;
  else if (substr=="return") lxd=_kwReturn;
  else if (substr=="break") lxd=_kwBreak;
  else if (substr=="cell") lxd=_kwCell;
  else if (substr=="group") lxd=_kwGroup;
  else if (substr=="if") lxd=_kwIf;
  else if (substr=="else") lxd=_kwElse;
  else if (substr=="display") lxd=_kwDisplay;
  else if (substr=="getline") lxd=_kwGetLine;
  else if (substr=="virtual") lxd=_kwVirtual;
  else if (substr=="const") lxd=_kwConst;
  else if (substr=="plot") lxd=_kwPlot;
  else if (substr=="matrix") lxd=_kwMatrix;
  else if (substr=="ring") lxd=_kwRing;
  else if (substr=="path") lxd=_kwPath;
  else if (substr=="rand") lxd=_kwRand;
  else if (substr=="log") lxd=_kwLog;
  else if (substr=="flush") lxd=_kwFlush;
  else if (substr=="append") lxd=_kwAppend;
  else if (substr=="pause") lxd=_kwPause;
  else if (substr=="float") lxd=_kwFloat;
  else if (substr=="int") lxd=_kwInt;

  if (lxd!=_lNa)
    substr="";

  return lexeme(substr, lxd);
}

vector <lexeme> lexical(Project&prj, string&code)
{
  printf("Performing lexical analysis...\n");
  vector <lexeme> seq;

  //readmode rm=rNA;

  size_t len = code.size();
  //size_t index=0;
  //bool decimal=false;

  char c=0;//current
  char n=code[0];//next

  for (size_t x=0; x<len; ++x)
  {
    c=code[x];
    n=code[x+1];

    if (isCompound(c))
    {
      bool cmpd=true;
      //printf("Compound %c detected\n", c);
      seq.push_back(getOperator(c, n, cmpd));
      if (cmpd) ++x;
    }
    else if (isQuote(c))
    {
      char lk = c=='\"'? c: '\'';
      size_t offset=x+1;
      for (; offset<len; ++offset)
        if (code[offset]==lk)
            break;
      if (offset==len)
        formatError(code, x, WRN_UNBOUND_QUOTE, prj);

      seq.push_back(lexeme(string(code.begin()+x+1, code.begin()+offset), lk=='\"'?_lString:_lChar));
      x=offset;
    }else if (isNumber(c))
    {
      bool decimal=false;
      size_t offset=x;
      for (; offset<len; ++offset)
      {
        if (code[offset]=='.')
        {
          if (decimal) break;
          decimal=true;
        }else if (!isNumber(code[offset]))
          break;
      }

      seq.push_back(lexeme(string(code.begin()+x, code.begin()+offset), decimal?_lFloat:_lInt));
      x=offset-1;
    }else
    {
      lexData lxd=_lNa;

      switch(c)
      {
        case ':': lxd=_lIndex; break;
        case ',': lxd=_lNItem; break;
        case '[': lxd=_lBodyOpen; break;
        case ']': lxd=_lBodyClose; break;
        case '(': lxd=_lArgOpen; break;
        case ')': lxd=_lArgClose; break;
        case '{': lxd=_lListOpen; break;
        case '}': lxd=_lListClose; break;
        case '.': lxd=_lRef; break;
        case ';': lxd=_lEnd; break;
      }
      if (lxd!=_lNa)
        seq.push_back(lexeme("", lxd));
      else if (!isDelim(c))
      {
        //identify symbol
        //printf("\nReading symbol %c %lu of %lu : [", c, x, len);
        size_t offset=x;
        //printf("%d>>%c\n", !isDelim(code[offset]), code[offset]);
        for (; offset<len; ++offset)
        {
          char t = code[offset];
          if (isDelim(t)) break;
          //else printf("%c", t);
        }
        //printf("]\n");
        seq.push_back(getSym(code, x, offset, prj));
        //seq.push_back(lexeme(string(code.begin()+x, code.begin()+offset), _lSymbol));
        x=offset-1;
      }
    }
  }

  if (prj.cdbg){
    printf("Lexical Token Stream...\n");
    for (lexeme lx: seq)
      printf("[%s : %d]", lx.raw.c_str(), lx.meta);
    printf("\n");
  }

  return seq;
}
