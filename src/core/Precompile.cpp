#include "Compilation.h"
#include "Error.h"
#include "Model.h"

#include <fstream>
#include <string>

#include <unistd.h>

using namespace std;

//update with aliases and other line modifiers
string updateLine(string line, Page&page)
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

      for (KeyPair kp : page.alia){
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

void parsePreCompilerDirective(string str, Config&config, Codestruct&codestruct, Page&page)
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
      for (string s : codestruct.sources)
      {
        if (a == s)
          {
            append=false;
            break;
          }
      }
      if (append){
        codestruct.sources.push_back(a);
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

    for (size_t x=0; x<page.alia.size(); ++x)
    {
      if (page.alia[x].key == key){
        addNew = false;

        for (size_t y=0; y<arguments.size(); ++y){
          //check for existing values
          bool append = true;
          for (size_t z=0; z<page.alia[x].values.size(); ++z)
          {
            if (arguments[y] == page.alia[x].values[z])
            {
              append=false;
              break;
            }
          }
          if (append)
            page.alia[x].values.push_back(arguments[y]);
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

      page.alia.push_back(keypair);

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

vector <Page> Precompile(Config&config, Codestruct&codestruct)
{
  vector <Page> pages;

  if (config.debug)
    printf("Starting precompilation\n");
  fflush(stdout);

  //format source files
  //interpret pre-preprocessor directives
  for (size_t x=0; x<codestruct.sources.size(); ++x)
  {
    Page page;
    //normal, precompiler directive
    enum {_pcNRM=0, _pcPCDIR, _pcSCMNT, _pcMCMNT};
    int state = _pcNRM;

    ifstream ifile((codestruct.sources[x].empty() ? "" : config.sourcePath + "/") + codestruct.sources[x]);

    if (!ifile)
    {
      postError(ERR_FNF, -1, codestruct.sources[x]);
      continue;
    }

    if (config.debug)
      printf("Loading %s\n", codestruct.sources[x].c_str());

    while(!ifile.eof())
    {
      string line;
      string buffer;
      getline (ifile, line);

      for (size_t y=0; y<=line.size(); ++y)
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
          switch (c)
          {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
            case 0:
            if (buffer.empty() || bitAction(state, _pcSCMNT, _bmCheck) || bitAction(state, _pcMCMNT, _bmCheck))
              continue;

            if (!_isOperator(line[y+1]) && !_isOperator(line[y-1]))
              buffer += ' ';

            //skip redundant white space
            else if (line [y+1] == ' '  ||
                line [y+1] == '\t' ||
                line [y+1] == '\r' ||
                line [y+1] == '\n' ||
                line [y] == 0      ||//short circuit terminator
                line [y+1] == 0)
                ++y;
            break;
            case '?':
              if (buffer.empty())
              {
                bitAction(state, _pcPCDIR, _bmSet);
              }
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
        parsePreCompilerDirective(buffer, config, codestruct, page);
        bitAction(state, _pcPCDIR, _bmClear);
      }else if (!buffer.empty())
      {
        buffer = updateLine(buffer, page);
        if (config.debug) printf("%s", buffer.c_str());
        if (state == _pcSCMNT)
          state = _pcNRM;
        page.raw +=  ' ' + buffer;
      }

      buffer.clear();
    }

    pages.push_back(page);
  }

  return pages;
}
