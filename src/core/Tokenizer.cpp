#include "Compilation.h"
#include "Util.h"

#include "Libs/KNX_Libraries/KNX_String.h"

//global, deal with it
bool debug=false;

//generate and append a token
Token * genToken(Token * current, LCode code, string&raw, size_t start, size_t end)
{
  Token*ret=new Token();

  ret->raw=string(raw.begin()+start, raw.begin()+end);
  ret->type=code;

  if (debug){
    if (code==lnan) printc(ret->raw, COLOR_WHITE);
    else if (code==lsym) printc(ret->raw, COLOR_RED);
    else if (code>=10 && code<80) printc(ret->raw, COLOR_CYAN);
    else if (code>=80 && code<90) printc(ret->raw, COLOR_BLUE);
    else if (code>=90 && code<100) printc(ret->raw, COLOR_YELLOW);
    else if (code>=100 && code<120) printc(ret->raw, COLOR_MAGENTA);
    else if (code>=120 && code<130) printc(ret->raw, COLOR_GREEN);
    else if (code>=130 && code<140) printc(ret->raw, COLOR_CYAN);
    else printc("[ERROR " + ret->raw + "]", COLOR_YELLOW);
  }

  if (current==NULL){
    ret->next=NULL;
    ret->previous=NULL;
    return ret;
  }else{
    ret->next=NULL;
    ret->previous=current;
    current->next=ret;
  }

  return ret;
}

//parse a token within a certain character
Token * parseBoundSymbol(Token*current, string&raw, size_t&index, size_t&cursor, LCode type, char echar)
{
  ++index;
  size_t xindex = index+1;
  while (raw[xindex]!=echar && raw[xindex]!=0) ++xindex;

  Token * ret = genToken(current, type, raw, index, xindex);

  index=xindex+1;
  cursor=xindex;

  return ret;
}

//parse an operator up to 3 characters
Token * parseOperator(Token*current, string&raw, size_t&index, size_t&cursor)
{
  size_t len=0;
  LCode code=lnan;

  char c2 = raw[index+1];
  char c3 = c2==0 ? 0 : raw[index+2];

  switch(raw[index]){
    //math and setters
    case '=':
      if (c2=='='){code = lequ; len=2;}
      else {code=lset; len=1;}
    break;
    case '+':
      if (c2=='='){code = landset; len=2;}
      else if (c2=='+'){code = linc; len=2;}
      else {code=ladd; len=1;}
    break;
    case '-':
      if (c2=='='){code = lsubset; len=2;}
      else if (c2=='-'){code = ldec; len=2;}
      else {code=lsub; len=1;}
    break;
    case '*':
      if (c2=='='){code = lmultset; len=2;}
      else {code=lmult; len=1;}
    break;
    case '/':
      if (c2=='='){code = ldivset; len=2;}
      else {code=ldivide; len=1;}
    break;
    case '%':
      code=lmod; len=1;
    break;
    case '^':
      code=lpow; len=1;
    break;
    case -5:
      code=lroot; len=1;
    break;
    //logical
    case '>':
      if (c2=='='){
        if (c3=='<'){code = lininc; len=3;}
        else{code = linex; len=2;}
      }else {code=lgtr; len=1;}
    break;
    case '<':
      if (c2=='='){
        if (c3=='>'){code = loutinc; len=3;}
        else{code = loutex; len=2;}
      }else {code=llss; len=1;}
    break;
    case '!':
      if (c2=='='){code = lnotequ; len=2;}
      else if (c2=='&'){code = lnand; len=2;}
      else if (c2=='|'){code = lnor; len=2;}
      else {code=lnot; len=1;}
    break;
    case '&':
      if (c2=='='){code = landset; len=2;}
      else {code=land; len=1;}
    break;
    case '|':
      if (c2=='='){code = lorset; len=2;}
      else if (c2=='|'){code = lxor; len=2;}
      else if (c2=='!'){code = lxnor; len=2;}
      else {code=lor; len=1;}
    break;
    //misc
    case ':': code=lindx; len=1; break;
    //case '?': code=lindx; len=1; break;
    //case '@': code=lindx; len=1; break;
    //case '$': code=lindx; len=1; break;
    //case '~': code=lindx; len=1; break;
    case ',': code=llist; len=1; break;
    case ';': code=lstop; len=1; break;
    case '[': code=lsbrk; len=1; break;
    case ']': code=lebrk; len=1; break;
    case '{': code=lsfnc; len=1; break;
    case '}': code=lefnc; len=1; break;
    case '(': code=lsprm; len=1; break;
    case ')': code=leprm; len=1; break;
    default:
    ++cursor;
    ++index;
    return current;
    break;
  }

  Token * ret = genToken(current, code, raw, index, index+len);

  index+=len;
  cursor+=len-1;

  return ret;
}

//parse ordinary expression (preserves reference operators)
Token * parseExpression(Token*current, string&raw, size_t&index, size_t&cursor, Codestruct&cs)
{
  size_t xindex = index;
  LCode code=lnan;
  while ((_isLetter(raw[xindex]) || _isNumber(raw[xindex]) || raw[xindex]=='.') && raw[xindex]!=0)
    ++xindex;

  string term(raw.begin()+index, raw.begin()+xindex);

  //check for keywords
  if (term=="if") code=lif;
  else if (term=="else") code=lelse;
  else if (term=="while") code=lwhile;
  else if (term=="break") code=lbreak;
  //types
  else if (term=="int") code=lint;
  else if (term=="dec") code=lfloat;
  else if (term=="state") code=lbool;
  else if (term=="char") code=lchar;
  else if (term=="string") code=lstring;
  else if (term=="cell") code=lcell;
  else if (term=="region") code=lgroup;
  else if (term=="array") code=larray;
  else if (term=="signal") code=lsignal;
  //modifiers
  else if (term=="override") code=loverride;
  else if (term=="final") code=lfinal;
  else if (term=="abstract") code=labstract;
  //keywords
  else if (term=="delete") code=ldel;
  else if (term=="new") code=lnew;
  else if (term=="goto") code=lelse;
  else if (term=="true") code=ltrue;
  else if (term=="false") code=lfalse;
  else if (term=="for") code=lfor;
  else if (term=="while") code=lwhile;
  //check for existing declarations
  else{
    code=lsym;
    bool exists = false;
    code=lsym;
    for (Symbol sym : cs.symbolTable){
      if (sym.raw == term){
        exists = true;
        break;
      }
    }

    Symbol symbol;
    symbol.raw=term;
    symbol.type=lsym;
    if (!exists) cs.symbolTable.push_back(symbol);
  }

  Token * ret = genToken(current, code, raw, index, xindex);

  index=xindex;
  cursor=xindex-1;

  return ret;
}

Token * parseNumber(Token*current, string&raw, size_t&index, size_t&cursor){
  size_t xindex = index;

  bool isDecimal=false;
  while ((_isNumber(raw[xindex]) || raw[xindex]=='.') && raw[xindex]!=0)
    {
      if (raw[xindex]=='.')
        isDecimal=true;
      ++xindex;
    }

  Token * ret = genToken(current, isDecimal ? lfloat : lint, raw, index, xindex);

  index=xindex;
  cursor=xindex-1;

  return ret;
}

//determine type of symbol
//if not a recognized keyword, add to symbol list
Token * resolveSymbol(string symbol, Codestruct&cs)
{
  Token * ret = new Token();

  return ret;
}

/*
Tokenization may make following assumptions:
Whitespace seperates symbols and numbers
Space is only legal whitespace
All operators, besides '.', will deliminate
*/
Token * Tokenize(Config&config, Codestruct&cs, vector<Page>&pages)
{
  if (config.debug) printf("Beginning Tokenization\n");

  debug=config.debug;

  Token * stream = NULL;

  for (Page page : pages){
    size_t len = page.raw.size();
    size_t index = 0;

    for (size_t x=0; x<len; ++x){
      char c = page.raw[x];
      if (c==' '){
        index=x+1;
        if (config.debug) printf(" ");
      }else if (_isQuote(c)){
        stream = parseBoundSymbol(stream, page.raw, index, x, c=='\''? lchar : lstring, c);
      }else if (_isOperator(c)){
        stream = parseOperator(stream, page.raw, index, x);
      }else if (_isLetter(c)){
        stream = parseExpression(stream, page.raw, index, x, cs);
      }else if (_isNumber(c)){
        stream = parseNumber(stream, page.raw, index, x);
      }else{
        //TODO throw error
        printf("[ERROR]\n");
        printc(c, COLOR_RED);
        index=x+1;
      }
    }
  }

  if (config.debug && cs.symbolTable.size()>0){
    printf("\n\n\n\n");

    //print object table
    printf("|---Symbol Table");
    for (int x=0; x<33; ++x) printf("-");
    printf("|\n");
    printf("|%-48s|\n", "");
    for (Symbol sym : cs.symbolTable){
      printf("\n|%-35s|%-12d|\n", sym.raw.c_str(), sym.type);
      printf("\n");
      for (int x=0; x<50; ++x) printf("-");
    }
  }

  if (stream == NULL)
    return NULL;

  //be kind, rewind
  while (stream->previous != NULL)
    stream = stream->previous;

  return stream;
}
