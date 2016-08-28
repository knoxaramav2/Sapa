#include "Compilation.h"
#include "Error.h"
#include "Model.h"

#include <fstream>
#include <string>

#include <unistd.h>

using namespace std;

char getEscapeCharacter(char c){

  switch(c){
    case '0': return 0;
    case 'n': return '\n';
    case 't': return '\t';
    case 'r': return '\r';
    case '\\': return '\\';
    case '\'': return '\'';
    case '\"': return '\"';
    case 'v': return '\v';
    case 'f': return '\f';
    case 'a': return '\a';
    case 'b': return '\b';
  }

  return c;
}

//update with aliases and other line modifiers
string updateLine(string line, Page&page, Codestruct&cs)
{
  size_t idx=0;
  for (size_t x=0; x<=line.size(); ++x)
  {
    if (!_isLetter(line[x]))
    {
      if (idx == x)
      {
        ++idx;
        continue;
      }

      string tmp = string(line.begin()+idx, line.begin()+x);

      for (KeyPair kp : cs.alia){
        for (string val : kp.values){
          if (val == tmp)
          {
            //printf("\n[replace %s with %s]\n", tmp.c_str(), kp.key.c_str());
            line.erase(line.begin()+idx, line.begin()+x);
            line.insert(idx, kp.key.c_str());
            idx = (x+=val.size()-kp.key.size());
            goto brk;
          }
        }
      }

      brk:;

      idx = x+1;
    }
  }

return line;
}

void parsePreCompilerDirective(string str, Config&config, Codestruct&cs, Page&page)
{
  string value;
  string::iterator index = str.begin();
  vector <string> arguments;

  if (config.debug) printf("Precomp: ");

  size_t len = str.size();

  for (size_t x=0; x<=len; ++x)
  {
    if (x == len || str[x]==' ')
    {
      if (index == str.begin()+x)
        ++index;
      else{
        string tmp(index, str.begin() + x);
        index = str.begin() + x + 1;

        if (value.empty())
          value = tmp;
        else
          arguments.push_back(tmp);
      }
    }
  }

  if (value == "import")
  {
    if (config.debug) printf("<import> ");

    if (arguments.size() == 0)
    {
      postError(WRN_BLANK_PRECMP, -1, str);
      return;
    }

    //prevent redundant file imports
    for (string a : arguments)
    {
      bool append = true;
      for (string s : cs.sources)
      {
        if (a == s)
          {
            append=false;
            break;
          }
      }
      if (append){
        cs.sources.push_back(a);
        printf("%s ", a.c_str());
      }
    }
  }else if (value == "psuedo")
  {
    if (config.debug) printf("<psuedo>");

    if (arguments.size() <= 1)
    {
      postError(WRN_BLANK_PRECMP, -1, str);
      return;
    }

    string key = arguments[0];
    arguments.erase(arguments.begin());

    //check for alias updates or conflicts
    bool addNew = true;

    for (size_t x=0; x<cs.alia.size(); ++x)
    {
      if (cs.alia[x].key == key){
        addNew = false;

        for (size_t y=0; y<arguments.size(); ++y){
          //check for existing values
          bool append = true;
          for (size_t z=0; z<cs.alia[x].values.size(); ++z)
          {
            if (arguments[y] == cs.alia[x].values[z])
            {
              append=false;
              break;
            }
          }
          if (append)
            cs.alia[x].values.push_back(arguments[y]);
          if (config.debug) printf("[%s] ", arguments[y].c_str());
        }
        break;
      }
    }

    if  (addNew)
    {
      KeyPair keypair;
      keypair.key = key;
      keypair.values = arguments;

      cs.alia.push_back(keypair);

      if (config.debug)
      {
        printf("(%s) ", keypair.key.c_str());
        for (string s: keypair.values) printf("[%s] ", s.c_str());
      }
    }
  }else{
    postError(ERR_SETTING, -1, str);
  }

  if (config.debug) printf("\n");
}

vector <Page> Precompile(Config&config, Codestruct&cs)
{
  vector <Page> pages;

  if (config.debug)
    printf("Starting precompilation\n");
  fflush(stdout);

  //format source files
  //interpret pre-preprocessor directives
  for (size_t x=0; x<cs.sources.size(); ++x)
  {
    Page page;
    //normal, precompiler directive
    enum {_pcNRM=0, _pcPCDIR, _pcSCMNT, _pcMCMNT};
    int state = _pcNRM;

    ifstream ifile((cs.sources[x].empty() ? "" : config.sourcePath + "/") + cs.sources[x]);

    if (!ifile)
    {
      postError(ERR_FNF, -1, cs.sources[x]);
      continue;
    }

    if (config.debug)
      printf("Loading %s\n", cs.sources[x].c_str());

    while(!ifile.eof())
    {
      string line;
      string buffer;
      getline (ifile, line);

      if (line.size() == 0)
        continue;

      //check if last character in line requires
      //appended whitespace
      if (page.raw.size()>0 ){
      char lchar = page.raw[page.raw.size()-1];
      char rchar = line[0];
      if (_isLetter(lchar) && _isLetter(rchar))
        buffer+=' ';
      }

      for (size_t y=0; y<line.size(); ++y)
      {
        char c = line[y];
        //special states
        if (bitAction(state, _pcSCMNT, _bmCheck) || bitAction(state, _pcMCMNT, _bmCheck))
        {
          if (state == _pcMCMNT)
          {
            if (line [y-1] == '*')
              bitAction(state, _pcMCMNT, _bmClear);
          }else{
              bitAction(state, _pcSCMNT, _bmCheck);
          }
        }else{
          if (bitAction(state, _pcSCMNT, _bmCheck) || (bitAction(state, _pcMCMNT, _bmCheck))){
            if (c=='#'){
              if (y > line.size() && line[y+1]=='*'){
                bitAction(state, _pcMCMNT, _bmClear);
              }else{
                bitAction(state, _pcSCMNT, _bmClear);
              }
              continue;
            }
          }

          switch (c)
          {
            //single LR context operators
            case '.':
            buffer+=c;
            if (_isWhitespace(line[y+1]))
              ++y;
            break;
            case '\\':
            buffer+=getEscapeCharacter(c);
            break;
            //whitespace redundancy check
            case ' ':
            case '\t':
            case '\n':
            case '\r':{
              /*
                Ignore whitespace where:
                  * preceeding or next value is operator or whitespace
                  * last value to page.raw is whitespace, if y == 0
              */
              c=' ';
              char next = line[y+1];

              if (y>0 && _isWhitespace(line[y-1]))
                continue;

              if (_isOperator(next) || ((line.size()>0) && (_isOperator(line[y-1]))))
                continue;

              if (y==0 && page.raw.size() > 0){
                if (_isOperator(page.raw[page.raw.size()-1])){
                  continue;
                }
              }

              buffer += ' ';
            }
            break;
            //state operators
            case '?':
            if (buffer.empty())
            {
              bitAction(state, _pcPCDIR, _bmSet);
            }else buffer += c;
            break;
            case '#':
            if (line [y+1] == '*'){
              bitAction(state, _pcMCMNT, _bmSet);
            }else{
              bitAction(state, _pcSCMNT, _bmSet);
              ++y;
            }
            break;
            default:
            if (bitAction(state, _pcSCMNT, _bmCheck) || bitAction(state, _pcMCMNT, _bmCheck))
              continue;

            buffer += c;
            break;
          }
        }
      }

      if (bitAction(state, _pcSCMNT, _bmCheck))
        bitAction(state, _pcSCMNT, _bmClear);

      //reset single line states
      if (bitAction(state, _pcPCDIR, _bmCheck)){
        parsePreCompilerDirective(buffer, config, cs, page);
        bitAction(state, _pcPCDIR, _bmClear);
      }else if (!buffer.empty()){
        buffer = updateLine(buffer, page, cs);
        if (config.debug) printf("%s", buffer.c_str());
        if (state == _pcSCMNT)
          state = _pcNRM;
        page.raw += buffer;
      }
      buffer.clear();
    }
    if (config.debug) printf("\n");
    pages.push_back(page);
  }

  return pages;
}
