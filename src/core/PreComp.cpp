#include "Compilation.h"
#include "Error.h"
#include "Libs/KNX_Libraries/KNX_String.h"

#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//false if illegal value
bool getAffirmativeResult(string argument, bool & setting)
{
  argument = toLowerc(argument.c_str());

  if (argument == "true" || argument == "yes" || argument == "1")
    {
      setting = true;
      return true;
    }
  if (argument == "false" || argument == "no" || argument == "0")
    {
      setting = false;
      return true;
    }

  setting = false;
  return false;
}

bool getFloatResult(string argument, float & value)
{
  if (isNumeric(argument.c_str()) == 0)
    return false;

  value = atof(argument.c_str());

  return true;
}

bool getIntResult(string argument, int & value)
{
  if (isNumeric(argument.c_str()) == 0)
    return false;
  if (isNumeric(argument.c_str()) == 2){
    postError(WRN_IMP_CAST, -1, argument, "");
    value = (int)atof(argument.c_str());
  }else
  {
    value = atoi(argument.c_str());
  }

  return true;
}

//copies unique entries to original
void appendList(vector<string>& original, vector<string>& addition)
{
  for (string item : addition)
  {
    bool doAppend = true;
    for (size_t x=0; x<original.size(); ++x)
    {
      if (original[x] == item)
      {
        doAppend = false;
        break;
      }
    }
    if (doAppend)
      original.push_back(item);
  }
}

void printConfigurations(Config & config)
{
  printf("Configuration details\n");
  printf("debug         %d\n", config.debug);
}

//attempt to load file and append to existing code
//return number of lines appended
size_t importFile(string file, vector <string> &code)
{
  ifstream srcFile(file+".nrn");

  if (!srcFile)
  {
    postError(ERR_FNF, -1, file, "");
    return 0;
  }

  while (!srcFile.eof())
  {
    string line;
    getline(srcFile, line);

    #ifdef __WINDOWS
    //erase \r
    line.erase(line.end()-1);
    #endif
  }

  return code.size();
}

//returns initial import list
vector <string> processCNS(Config & config)
{
  vector <string> importList;

  ifstream cns(config.srcFile);

  if (!cns)
    {string tmp; postError(ERR_NO_CNS, -1, tmp, "");}

  while (!cns)
  {
    string line;
    getline(cns, line);
    line = toLowerc(line.c_str());

    //split terms, remove comments
    vector <string> terms;
    size_t index = 0;
    for (size_t x = 0; x<=line.size(); ++x)
    {
      if (line[x] == ' ' || line[x] == '\0' || line[x] == '\r')
      {
        if (index != x)
          terms.push_back(string(line.begin()+index, line.begin()+x));
        index = x + 1;
      }
    }

    if (terms.size() == 0)
      continue;

    string setting = terms[0];
    terms.erase(terms.begin());
    size_t settingArgs = terms.size();

    //check against current settings
    if (setting == "experimental" && settingArgs == 1){
      if (!getAffirmativeResult(terms[0], config.experimental))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "debug" && settingArgs == 1){
      if (!getAffirmativeResult(terms[0], config.prjDebug))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "static" && settingArgs == 1){
      if (!getAffirmativeResult(terms[0], config.staticObjects))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "title" && settingArgs == 1){config.projectName = terms[0];} else
    if (setting == "version" && settingArgs == 1){config.projectVersion = terms[0];} else
    if (setting == "language" && settingArgs == 1){config.targetLanguage = terms[0];} else
    if (setting == "import") {appendList(importList, terms);} else
    if (setting == "nmax" && settingArgs == 1){
      if (!getIntResult(terms[0], config.maxObjects))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "ntran" && settingArgs == 1){
      if (!getIntResult(terms[0], config.signalLength))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "tdf" && settingArgs == 1){
      if (!getFloatResult(terms[0], config.TDF))
        postError(ERR_SETTING_VALUE, -1, setting, "");} else
    if (setting == "rsp" && settingArgs == 1){
      if (!getFloatResult(terms[0], config.GRP))
        postError(ERR_SETTING_VALUE, -1, setting, "");}
    else
      postError(ERR_SETTING_VALUE, -1, setting, "");

  }

  cns.close();

  return importList;
}

dataFile preCompile (Config & config)
{
  dataFile dfile;
  vector <string> imports;

  imports = processCNS(config);


  return dfile;
}
