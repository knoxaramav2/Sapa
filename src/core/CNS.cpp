#include "Libs/KNX_Libraries/KNX_String.h"

#include "Compilation.h"

#include <fstream>
#include <string>
#include <vector>

#include <stdio.h>
#include <unistd.h>

using namespace std;

struct vmodel{
  string field;
  vector <string> values;
};

bool validateBool(vmodel&model, bool&setting)
{
  if (model.values.size()!=1){
    postError(ERR_SETTING_VALUE, -1, model.field);
    setting=false;
    return false;
  }

  if (strncmp(toLowerc(model.values[0].c_str()) , "true", 4) == 0) setting=true;
  else if (strncmp(toLowerc(model.values[0].c_str()) , "false", 5) == 0) setting=false;
  else {
    postError(ERR_SETTING_VALUE, -1, model.field);
    setting=false;
    return false;
  }

  return true;
}

bool validateString(vmodel&model, string&setting)
{
  if (model.values.size()!=1){
    postError(ERR_SETTING_VALUE, -1, model.field);
    setting="";
    return false;
  }

  setting = model.values[0];

  return true;
}

bool validateNumeric(vmodel&model, float&setting)
{
  if (model.values.size()!=1){
    postError(ERR_SETTING_VALUE, -1, model.field);
    setting=false;
    return false;
  }

  if (isNumeric(model.values[0].c_str()) != 0) setting=(float)atof(model.values[0].c_str());
  else {
    postError(ERR_SETTING_VALUE, -1, model.field);
    setting=0;
    return false;
  }

  return true;
}

Codestruct LoadCNS(Config&config)
{
  if (config.debug) printf("Loading %s\n", config.cns.c_str());

  ifstream ifile(config.cns);

  if (!ifile)
  {
    postError(ERR_NO_CNS, -1, config.cns);

    return Codestruct();
  }

  vector <vmodel> models;

  while(!ifile.eof())
  {
    string line;
    string buffer;
    vmodel model;
    getline (ifile, line);

    #ifdef __WINDOWS
    line[line.size()-1]=0;
    #endif

    int state = 0;

    for (size_t x = 0; x <= line.size(); ++x)
    {
      char c = line[x];

      if (c==' ' || c=='\t' || c=='\n' || c==0)
      {
        if ((state==0 || c==0) && state!=2)//normal (always accept end of line)
        {
          //printf(">> %s\n", buffer.c_str());

          if (buffer.empty()) continue;

          if (model.field.empty()) model.field = buffer;
          else model.values.push_back(buffer);

          buffer.clear();
        }else if (state==1)//ignore
        {
          continue;
        }else if (state==2)//accept all
        {
          if (c=='\\')
          {
            ++x;
            //set append following escape character
          }
          else buffer += c;
        }
      }else if (c=='\'' || c=='\"')
      {
        state = state==0? 2 : 0;
      }else if (c=='#')
      {
        state = state==0? 1 : 0;
      }else if (c=='\\')
      {
        ++x;
        buffer+=c;
      }else{
        if (state != 1)
          buffer += c;
      }
    }

    if (!model.field.empty())
    {
      models.push_back(model);
    }
  }

  //validate and assign CNS configurations

  Codestruct codestruct;

  for (vmodel model: models)
  {
    if (config.debug)
    {
      printf("%s:\t\t", model.field.c_str());

      for (string s : model.values)
      {
        printf("[%s]\t", s.c_str());
      }

      printf("\n");
    }

    //CNS settings here **********************************************

    if (strncmp(toLowerc(model.field.c_str()) , "import", 6) == 0)
    {
      //ensure import file is not currently on the list
      for (string newsrc : model.values)
      {
        bool duplicate = false;

        for (string existsrc : codestruct.sources)
        {
          if (existsrc == newsrc)
          {
            duplicate = true;
            break;
          }
        }

        if (duplicate == false)
        {
          codestruct.sources.push_back(newsrc);

          if (config.debug) printf("added %s to import list\n", newsrc.c_str());
        }
      }
    }else if (strncmp(toLowerc(model.field.c_str()) , "experimental", 11) == 0){
        if (validateBool(model, config.experimental) && config.debug) printf("experimental set to %s\n", config.experimental ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "optimize", 8) == 0){
        if (validateBool(model, config.optimize) && config.debug) printf("optimize set to %s\n", config.optimize ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "debug", 5) == 0){
        if (validateBool(model, config.cdbg) && config.debug) printf("debug set to %s\n", config.cdbg ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "makectm", 7) == 0){
        if (validateBool(model, config.ctm) && config.debug) printf("connectome build set to %s\n", config.ctm ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "makerte", 7) == 0){
        if (validateBool(model, config.rte) && config.debug) printf("runtime engine build set to %s\n", config.rte ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "static", 6) == 0){
        if (validateBool(model, config.cstatic) && config.debug) printf("static set to %s\n", config.cstatic ? "true" : "false");
    }else if (strncmp(toLowerc(model.field.c_str()) , "title", 5) == 0){
        if (validateString(model, config.projectName) && config.debug) printf("project name set to %s\n", config.projectName.c_str());
    }else if (strncmp(toLowerc(model.field.c_str()) , "version", 7) == 0){
        if (validateString(model, config.version) && config.debug) printf("version set to %s\n", config.version.c_str());
    }else if (strncmp(toLowerc(model.field.c_str()) , "language", 7) == 0){
        if (validateString(model, config.language) && config.debug) printf("version set to %s\n", config.language.c_str());
    }else if (strncmp(toLowerc(model.field.c_str()) , "rsp", 3) == 0){
        if (validateNumeric(model, config.rsp) && config.debug) printf("default resting potential set to %f\n", config.rsp);
    }else if (strncmp(toLowerc(model.field.c_str()) , "tdf", 3) == 0){
        if (validateNumeric(model, config.tdf) && config.debug) printf("time dialation factor set to %f\n", config.tdf);
    }else if (strncmp(toLowerc(model.field.c_str()) , "nmax", 4) == 0){
        if (validateNumeric(model, config.nmax) && config.debug) printf("nerual max set to %f\n", config.nmax);
    }else if (strncmp(toLowerc(model.field.c_str()) , "ntran", 5) == 0){
        if (validateNumeric(model, config.ntran) && config.debug) printf("transmitter size set to %f\n", config.ntran);
    }
  }

  return codestruct;
}
