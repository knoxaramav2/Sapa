#include "Project.hpp"
#include "Error.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <cstdlib>

#include <fstream>

#include "Libs/KNX_Libraries/KNX_String.h"
#include "Libs/KNX_Libraries/KNX_Hash.h"

using namespace std;

Project::Project(string cnsName)
{
//  #ifdef __WINDOWS

  char path[256];
  char dest[256];
  //struct stat info;
  //pid_t pid = getpid();
  sprintf(path, "/proc/self/exe");
  readlink(path, dest, 256);

  localAddr = dest;

  #ifdef __WINDOWS
  //remove cygwin path
  localAddr.erase(localAddr.begin(), localAddr.begin()+10);
  localAddr.erase(localAddr.end()-3, localAddr.end());
  localAddr.insert(localAddr.begin()+1, ':');
  #else
  localAddr.erase(localAddr.end()-3, localAddr.end());
  #endif

  localAddr = localAddr + "/Projects/";
  cnsFile=cnsName;

  //******Setup flags*******

  //compilation
  ddbg=false;
  cdbg=false;
  vEW=false;
  makeCTM=false;
  makeRTE=false;
  binaryComp=false;
  mkFile=false;

  //RTE
  ddbg=false;
  transSize=1;

  c_scan=false;
  c_lex=false;
  c_build=false;

  bLevel=_noBuild;
  useLclDir=false;
}

void Project::fncImport(vector <string> list, string line)
{
  if (list.size()==0)
    return;

  //printf("%s%sfound\n", list[0].c_str(), registry.hasEntry(list[0])?" ":" not ");

  //registry.update("imports", list, true, false);
  registry.update("import", (void*)&list, _list, true, false);
}

void Project::fncDatSet(vector <string> list, string line)
{
    if (list.size()!=2)
      {
        postError(line, "", ERR_EXPCT_ARG, -1, 0);
        return;
      }

    regType r = registry.getType(list[0]);

    if (r==_NA)
      {
        postError(line, "", ERR_REG_NOT_FOUND, -1, 0);
        return;
      }

    switch(r)
    {
      case _bool:{
      if (list.size()!=2)
        {
          postError(line, "", ERR_INV_CNS_ARG, -1, 0);
          return;
        }
      if (list[1]!="true" && list[1]!="false")
      {
        postError(line, "", ERR_INV_CNS_ARG, -1, 0);
        return;
      }
      bool arg=list[1]=="true"?true:false;
      registry.update(list[0], (void*) &arg, _bool, true, false);
      break;}
      case _numeric:{
      //printf("%s %s %d\n", list[0].c_str(), list[1].c_str(), isNumeric(list[1].c_str()));
      if (list.size()!=2)
        {
          postError(line, "", ERR_INV_CNS_ARG, -1, 0);
          return;
        }
      if (isNumeric(list[1].c_str())==0)
      {
        postError(line, "", ERR_INV_CNS_ARG, -1, 0);
        return;
      }
      float arg=(float)atof(list[1].c_str());
      registry.update(list[0], (void*) &arg, _numeric, true, false);
      break;}
      case _string:{
      if (list.size()!=2)
        {
          postError(line, "", ERR_INV_CNS_ARG, -1, 0);
          return;
        }
      string arg = list[1];
      registry.update(list[0], (void*) &arg, _string, true, false);
      break;}
      case _psuedo:{
      if (list.size()!=2)
        {
          postError(line, "", ERR_INV_CNS_ARG, -1, 0);
          return;
        }
      string arg = list[1];
      registry.update(list[0], (void*) &arg, _psuedo, true, false);
      break;}
      case _list:{
      list.erase(list.begin());
      vector <string> arg = list;
      registry.update(list[0], (void*) &arg, _string, true, false);
      break;}
      case _NA:
        postError(line, "", ERR_INV_CNS_ARG, -1, 0);
        return;
      break;
    }

  //registry.update("imports", (void*)list, _list, true, false);
}

bool Project::loadCNS()
{
  //parse CNS file
  ifstream ifile (localAddr+cnsFile+"/"+cnsFile+".cns");

  //printf(">> %s\n", string(localAddr+cnsFile+"/"+cnsFile+".cns").c_str());

  if (!ifile)
  {
    postError(cnsFile, "", ERR_CNS_404, -1, 0);
    return false;
  }

  while (!ifile.eof())
  {
    string line;
    getline (ifile, line);

    #ifdef __WINDOWS
    //remove carriage return
    line[line.size()-1]=0;
    #endif
    //printf("%s\n", line.c_str());

    //parse and identify imports/sets
    //1=import, 2=set

    //very simplistic parser. TODO upgrade later
    int command=0;
    string identifier;
    vector <string> arguments;
    string buffer;
    bool comment=false;
    bool quote=false;
    for (unsigned x=0; x<=(unsigned)line.size(); ++x)
    {
      char c = line[x];

      if (comment || quote)
      {
        if (comment && c=='#')
          comment=false;
        else if (quote)
        {
          if (c=='\\'){
            if (x+1<line.size())
              buffer+=line[++x];
            else
            {
              postError(line, "", WRN_UNBOUND_QUOTE, -1, 0);
              arguments.push_back(buffer);
            }

            }
          else if (c=='\"')
            {
              arguments.push_back(buffer);
              buffer.clear();
              comment=false;
            }
          else buffer+=c;
        }
        continue;
      }

      if (c==0)
      {
        if (buffer.size()>0)
          arguments.push_back(buffer);
        buffer.clear();
      }
      else if (c=='^' || c=='=')
      {
        if (buffer.size()!=0)
          postError(line, "", ERR_ARG_BFR_COM, -1, 0);
        if(command!=0)
          postError(line, "", ERR_MULT_COM, -1, 0);
        else
          command=c=='^'?1:2;
      }
      else if (c==' ' || c=='\t')
      {
        if (buffer.size()>0)
          {
            arguments.push_back(buffer);
            buffer.clear();
          }
      }
      else if (c=='#')
      {
        comment=true;
      }else if (c=='\"')
      {
        quote=true;
      }else
        buffer+=c;
    }

    if (buffer.size()!=0)
      {
        arguments.push_back(buffer);
        buffer.clear();
      }

    //interpret command
    if (command==0 && arguments.size()!=0)
      postError(line, "", ERR_ARG_BFR_COM, -1, 0);
    else if (command!=0)
    {
      //import
      if (command==1)
        fncImport(arguments, line);
      else
        fncDatSet(arguments, line);
    }
  }
  return true;
}

bool Project::setCNS(string src)
{
  if (!cnsFile.empty())
    return false;
  cnsFile=src;
  return true;
}

bool Project::hasCNS()
{
  return !cnsFile.empty();
}

string Project::getLAddr()
{
  return localAddr;
}

void Project::setBuildLevel(buildLevel bl)
{
  bLevel = bl>bLevel?bl:bLevel;
}

string Project::formatPath(string fname, string ext)
{
  if (!useLclDir)
    return fname+ext;
  return localAddr+cnsFile+"/"+fname+ext;
}
