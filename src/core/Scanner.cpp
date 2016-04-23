#include "Compilation.hpp"
#include "Error.hpp"

#include <stdio.h>
#include <fstream>

using namespace std;

/*
  Scans all files to generate skeleton structure of project
  Returns signature string
*/

//scan line-by-line for type definitions
//look for tokens following 'def' and 'psuedo'

string scanner(Project&prj)
{
  string signature;

  RegItem * rt = prj.registry.getItem("imports");

  if (rt==NULL)
    return "";

  vector<std::string> * imports = (vector<std::string>*)rt->info;

  if (prj.cdbg)
  {
    printf("Imports found\n");
    for (size_t x=0; x<imports->size(); ++x)
      printf(">>\t%s\n",(*imports)[x].c_str());
  }

  for (size_t x=0; x<imports->size(); ++x)
  {
    string impStr(prj.getLAddr()+"test"+"/"+"src"+".nrn");
    ifstream ifile (impStr);
    if (!ifile)
      {
        printf("Nope\n");
        postError(impStr, "", ERR_IMRT_NOT_FOUND, -1, 0);
        return "";
      }

      printf("%s...\n\n", impStr.c_str());
    while (!ifile.eof())
    {
      string buffer;
      getline(ifile, buffer);
      if (buffer.size()>0)
        printf("%s\n", buffer.c_str());
    }
  }


  return signature;
}

/*
Declaration symbols

This identifies interfaces and type declarations, such as objects
and their respective methods, to ensure CTM compatibility across
runtime enviornments.

format is a sequence of hex tags of the form: [identifier][type]:[member1].[type]-[member2].[type];
nested objects are written such:
  [object].[type]:[subobject1].[type];[subobject2].[type]:[sub-subobject].type;;

*/
