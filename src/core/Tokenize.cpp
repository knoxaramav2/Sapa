#include "Error.h"
#include "Compilation.h"

#include <string>
#include <vector>
#include <fstream>

dataFile preCompile(Config & config)
{
  dataFile dfile;

  ifstream cns(config.srcFile);

  while (!cns.eof())
  {
    string line;
    vector <string> segments;

    getline(cns, line);

    size_t index=0;
    for (size_t x=0; x<=line.size(); ++x)
    {
      if (line[x] == ' ' || line[x] == '\0')
      {
        if (index != x)
        {
          segments.insert(string(line.begin()+index, line.begin()+x));
          index = x+1;
        }
      }
    }
  }


  cns.close();

  return dfile;
}
