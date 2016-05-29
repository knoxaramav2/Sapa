#include "Compilation.h"
#include "Error.h"
#include "Libs/KNX_Libraries/KNX_String.h"

#include <fstream>
#include <string>

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
    if (setting == "experimental" && settingArgs == 1)
      if (!getAffirmativeResult(terms[0], config.experimental))
        postError(ERR_SETTING_VALUE, -1, setting, "");
    if (setting == "debug" && settingArgs == 1)
      if (!getAffirmativeResult(terms[0], config.debug))
        postError(ERR_SETTING_VALUE, -1, setting, "");

    else if (setting == "optimize" && settingArgs == 1)

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
