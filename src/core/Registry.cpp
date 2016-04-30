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
addItem("makeRTE", true, _bool);
addItem("makeCTM", true, _bool);

addItem("RSP", true, _numeric);
addItem("TDF", true, _numeric);
addItem("NGEN", true, _bool);
addItem("NMAX", true, _numeric);
addItem("NTRAN", true, _numeric);

addItem("import", true, _list);
}

//symbol, reserved access, registry type
bool Registry::addItem(string line, bool res, regType rt)
{
  if (hasEntry(line))
  {
    return false;
  }else
  {//new entry
    RegItem reg;

    reg.hash=FNV_1a(line.c_str());
    reg.raw=line;
    reg.reserved=res;
    reg.type=rt;
    reg.toggle=false;

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
      case _psuedo:
      case _list:
      reg.info = new vector <string>;
      break;
      default:
      return false;
      break;
    }

    listing.push_back(reg);
  }

  return true;
}

regType Registry::getType(string id)
{
  unsigned long long hash = FNV_1a(id.c_str());

  for (unsigned x=0; x<(unsigned) listing.size(); ++x)
    if (hash==listing[x].hash)
      return listing[x].type;

  return _NA;
}

//symbol, data, registry type, reserved access, replace
bool Registry::update(string str, void*info, regType rtype, bool res, bool rep)
{
  //if entry not found, create new
  if (!hasEntry(str))
    addItem(str, res, rtype);

  unsigned long long hash = FNV_1a(str.c_str());

  for (unsigned x=0; x<listing.size(); ++x)
    if(listing[x].hash==hash)
      {
        if (rtype!=listing[x].type)
          {
            postError(str, "", ERR_REG_NCMP_TYPE, -1, 0);
            return false;
          }else
          {
            switch(rtype)
            {
              case _bool:
              *(bool*)listing[x].info = *(bool*) info;
              break;
              case _numeric:
              *(float*)listing[x].info = *(float*) info;
              break;
              case _string:
              *(string*)listing[x].info = *(string*) info;
              break;
              case _psuedo:
              case _list:{
              RegItem * ritem = &listing[x];

              if (rep)
              {
                *(vector <string>*)ritem->info=*(vector<string>*)info;
              }else
              {
                ((vector <string>*)ritem->info)->insert(((vector <string>*)ritem->info)->end(), ((vector<string>*)info)->begin(), ((vector<string>*)info)->end());
              }
              //if (rep)
              //  *(vector <string>*)listing[x].info.insert(*(vector<string>*)listing[x].end(), *(vector<string>*)info.begin(), *(vector<string>*).end());
              //else
              //  *(vector <string>*)listing[x].info = *(vector <string>*) info;
              }
              break;
              case _NA:

              break;
            }
          }
      }

  return false;
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
      case _psuedo:
      case _list:
      strType = "list";
      if (listing[x].info!=NULL)
        {
          vector <string> list = *(vector <string>*)listing[x].info;
          valType="";
          for (unsigned x=0; x<list.size(); ++x)
          {
            //TODO make better way to display lists
            valType+=list[x];
          }

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

bool Registry::toggleItem(string title)
{
  RegItem * ri = getItem(title);
  if (ri==NULL)
    return false;

  ri->toggle=!ri->toggle;

  return true;
}

bool Registry::setItem(string title)
{
  getItem(title)->toggle=true;
  return true;
}

bool Registry::unsetItem(string title)
{
  getItem(title)->toggle=false;
  return true;
}

RegItem * Registry::getItem(string identifier)
{
  long long unsigned hash = FNV_1a(identifier.c_str());

  for (size_t x=0; x<listing.size(); ++x)
    if (listing[x].hash==hash)
      return &listing[x];

  return NULL;
}

vector <RegItem*> Registry::getAllOfType(regType rt)
{
  vector <RegItem*> ret;

  for (size_t x=0; x<listing.size(); ++x)
    if (listing[x].type==rt)
      ret.push_back(&listing[x]);

  return ret;
}
