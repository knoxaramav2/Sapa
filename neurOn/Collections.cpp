#include "Collections.h"

void SourceRegistry::addEntry(string item)
{
  list.push_back(item);
}

string SourceRegistry::popEntry()
{
  if (list.size()==0)
    return "";
  string buff=list[list.size()-1];
  list.erase(list.begin()+list.size()-1);
  return buff;
}

string SourceRegistry::getEntry()
{
  return list[list.size()-1];
}

void SourceRegistry::clearList()
{
  list.clear();
}

bool SourceRegistry::isEmpty()
{
  return (list.size()==0);
}
