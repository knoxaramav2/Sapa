#include "Compilation.hpp"

#include "Project.hpp"
#include "Error.hpp"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

//TODO Ignore fact that's it just a precompiler and make it pretty

vector <string> usedImports;

struct psuedo
{
  string target;
  vector <string> alias;
};

bool validateImport(string filename)
{
  for (size_t x=0; x<usedImports.size(); ++x)
  {
    //printf("%s >> %s\n", filename.c_str(), usedImports[x].c_str());
    if (filename==usedImports[x])
      return false;
  }

  usedImports.push_back(filename);
  return true;
}

string loadNrnFile(string filename, Project&prj)
{
  string buffer;

  if (prj.cdbg)
    printf("Loading %s\n", filename.c_str());

  //prevents file from being loaded multiple times

  ifstream ifile(prj.formatPath(filename, ".nrn"));
  if (!ifile)
  {
    postError(prj.formatPath(filename, ".nrn"), "", ERR_IMRT_NOT_FOUND, -1, prj.noErr);
  }
  else
  {
    if (prj.cdbg)
      printf("Parsing %s\n", prj.formatPath(filename, ".nrn").c_str());

    while(!ifile.eof())
    {
      string line;
      getline(ifile, line);

      #ifdef __WINDOWS
      //buffer[buffer.size()-1]=0;
      if (line.size()>1)
        line.erase(line.begin()+line.size()-1);
      else
        continue;
      #endif

      line+='\n';
      //printf("%s", line.c_str());
      //fflush(stdout);

      //buffer.insert(buffer.end(), line.begin(), line.end());
      buffer+=line;
    }

    if (prj.cdbg)
        printf("%s.nrn\n%s\n", filename.c_str(), buffer.c_str());
  }

  return buffer;
}

void exImport(string&str, size_t s, size_t e)
{

}

void exPsuedo(string&str, size_t s, size_t e)
{

}

void exPreCom(string&str, size_t s, size_t e, Project&prj)
{
vector <string> terms;
string command;
size_t sindex=s+1;
bool first=false;

for (size_t x=s+1; x<=e; ++x)
{
  if (str[x]==' ' || str[x]=='\n')
  {
    if (sindex!=x)
    {
      string seg(str.begin()+sindex, str.begin()+x);
      if (!first)
        {
          first=true;
          command = seg;
        }
      else
      {
        terms.push_back(seg);
      }
    }
    sindex=x+1;
  }
}

if (command=="import")
{
  for (size_t x=0; x<terms.size(); ++x)
  {
    if (!validateImport(terms[x]))
    {
      terms.erase(terms.begin()+x);
      --x;
    }else
    {
      str+=loadNrnFile(terms[x], prj);
    }
  }
  vector <string> * pTerm = new vector <string> ();
  for (string s : terms)
    pTerm->push_back(s);
  prj.registry.update(command, (void*)pTerm, _list, true, false);
}else
if (command=="psuedo")
{
  if (terms.size()<2)
    {
      postError(string(str.begin()+s, str.begin()+e), "Must have at least 2 arguments", ERR_MSS_PARAM, -1, prj.noErr<<1);
    }
  else
  {
    vector <string> * pTerm = new vector <string> ();
    string title = terms[0];
    terms.erase(terms.begin());
    for (string s : terms)
      pTerm->push_back(s);
//    printf("Made psuedo %s : %s\n", title.c_str(), terms[0].c_str());
    prj.registry.addItem(title, true, _psuedo);
    prj.registry.update(title, (void*)pTerm, _psuedo, true, false);
  }
}
str.erase(str.begin()+s, str.begin()+e+1);

}

string preProcessor(Project&prj)
{
  vector <string> * flist = (vector<string>*)prj.registry.getItem("import")->info;
  vector <psuedo> rep;
  vector <string> buffStack;
  rawscript rs;
  string rcode;
  char mode=0;
  size_t sIndex=0;//start of preproc command

  usedImports=*((vector<string>*)prj.registry.getItem("import")->info);


  //load project source files
  for (string sfile : *flist)
  {
    rcode+=loadNrnFile(sfile, prj);
  }

  size_t len = rcode.size();
  for (size_t x = 0; x < len; ++x)
  {
    //comments
    if (rcode[x]=='#')
    {
      size_t tpos=0;
      size_t start = 0;
      tpos = x+1;
      start = x;
      bool multiline=false;
      if (rcode[x+1]=='*')
      {
        ++tpos;
        multiline=true;
      }

      for (size_t y=tpos; y < len; ++y)
      {
        if (multiline)
        {
          if ((rcode[y] == '*' && rcode[y+1] == '#') || rcode[y+1]=='\0')
          {
            tpos=y+2;
            break;
          }
        }else
        {
          if (rcode[y]=='#' || rcode[y]=='\n')
          {
            tpos=y+1;
            break;
          }
        }
      }
      //printf("From %ld to %ld : Erasing [%s]\n", start, tpos, string(rcode.begin()+start, rcode.begin()+tpos).c_str());
      len = len-(tpos-start);
      rcode.erase(rcode.begin()+start, rcode.begin()+tpos);
      --x;
    }

    if (rcode[x]=='?')
    {
      sIndex=x;
      mode='?';
    }

    if (rcode[x]=='\n' && mode!=0)
    {
      exPreCom(rcode, sIndex, x, prj);
      mode=0;
      x=sIndex-1;
      len=rcode.size();
    }

    if (rcode[x]=='\\' && rcode[x+1]!='\0')
    {
      len-=2;
      rcode.erase(rcode.begin()+x,rcode.begin()+x+1);
      --x;
    }
  }

  //Perform psuedo operations

  vector <RegItem*> psuList = prj.registry.getAllOfType(_psuedo);

  len = rcode.size();
  //bool found=false;

  for (size_t l=0; l<psuList.size(); ++l)
  {
    //check each instance of each item
    string target=psuList[l]->raw;
    vector <string> * alia = (vector<string>*)(psuList[l]->info);
    for (size_t m=0; m<alia->size(); ++m)
    {
      size_t sloc = rcode.find(alia->at(m));
      if (sloc==string::npos)
        continue;

      bool lSet=false, rSet=false;
      //ensure define is individual string
      if (sloc>0)
      {
        if (isDelim(rcode[sloc-1]))
          lSet=true;
      }
      else
        lSet=true;

      if (isDelim(rcode[sloc+alia->at(m).size()]))
      {
        rSet=true;
      }

      if (lSet && rSet)
      {
        int orig = (int)alia->at(m).size();
        int rep = (int)target.size();

        if (prj.cdbg)
          printf("Psuedo: %s > %s\n", alia->at(m).c_str(), target.c_str());

        rcode.erase(rcode.begin() + sloc, rcode.begin() + sloc + orig);
        rcode.insert(rcode.begin() + sloc, target.begin(), target.end());

        len += orig-rep;
      }
    }
  }

  if (prj.cdbg)
  {
    printf("Precomp File.....\n\n");
    printf("%s\n", rcode.c_str());
    //prj.registry.printItems();
  }

  return rcode;
}

/*
Performs initial scanning of files, reading imports, psuedo's, and
reducing code into more easily parsed form
*/
