#include "Registry.hpp"
#include "Error.hpp"

#include "Libs/KNX_Libraries/KNX_Hash.h"

#include <stdio.h>
#include <sstream>

Registry::Registry()
{
#if BITMODE == 64

#else

#endif

//TODO replace with bitmode specific version
addItem("evolution", true, _bool);
addItem("optimize", true, _bool);
addItem("debug", true, _bool);
addItem("title", true, _string);
addItem("version", true, _string);
addItem("language", true, _string);
addItem("prsvSymb", true, _bool);

addItem("RSP", true, _numeric);
addItem("TDF", true, _numeric);
addItem("NGEN", true, _bool);
addItem("NMAX", true, _numeric);
addItem("NTRAN", true, _numeric);

addItem("imports", true, _list);
}

void Registry::addItem(string line, bool res, regType rt)
{
  if (hasEntry(line))
  {//update existing

  }else
  {//new entry
    RegItem reg;

    reg.hash=FNV_1a(line.c_str());
    reg.raw=line;
    reg.reserved=res;
    reg.type=rt;

    printf("Add %s %llu\n", line.c_str(), FNV_1a(line.c_str()));
    printf("Add %s %llu\n", line.c_str(), FNV_1a(line.c_str()));

    switch(rt)
    {
      case _bool:
      reg.info = new bool(false);
      break;
      case _numeric:
      reg.info = new float(0.0f);
      break;
      case _string:
      reg.info = new string;
      break;
      case _list:
      reg.info = new vector <string>;
      break;
      default:

      break;
    }

    listing.push_back(reg);
  }
}

regType Registry::getType(string id)
{
  unsigned long long hash = FNV_1a(id.c_str());

  for (unsigned x=0; x<(unsigned) listing.size(); ++x)
    if (hash==listing[x].hash)
      return listing[x].type;

  return _NA;
}

bool Registry::update(string str, void*, regType rtype, bool acc, bool rep)
{
  //if entry not found, create new

  return true;
}

void Registry::printItems()
{
  bool shaded=false;

  size_t len = listing.size();

  for (size_t x=0; x<len; ++x)
  {
    string strType;
    string valType="NULL";

    switch(listing[x].type)
    {
      case _bool:
      strType="bool";
      if (listing[x].info!=NULL)
        valType=*(bool*)listing[x].info?"true":"false";
      break;
      case _numeric:
      strType="numeric";
      if (listing[x].info!=NULL)
      {
        stringstream ss (stringstream::in | stringstream::out);
        ss << *(float*)listing[x].info;
        valType = ss.str();
      }
      break;
      case _string:
      strType="string";
      if (listing[x].info!=NULL)
        valType=*(string*)listing[x].info;
      break;
      case _list:
      strType = "list";
      if (listing[x].info!=NULL)
        {
          vector <string> list = *(vector <string>*)listing[x].info;
          valType="";
          for (unsigned x=0; x<list.size(); ++x)
              valType+=list[x]+"\n";
        }
      break;
      default:
      strType="Error";
    }

    printf("\033[%s|%-15s|%-3s|%-10s|%-20s|%-20llu\033[0m\n", (shaded=!shaded)?"1;30;47m":"1;37;40m",\
    listing[x].raw.c_str(), listing[x].reserved?"rsv":"---",strType.c_str(), valType.c_str(), listing[x].hash);
  }

}

bool Registry::hasEntry(string nLine)
{
  unsigned long long hashEntry = FNV_1a(nLine.c_str());

  for (unsigned x=0; x<listing.size(); ++x)
    if (hashEntry == listing[x].hash)
      return true;
  return false;
}
