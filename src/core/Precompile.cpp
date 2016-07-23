#include "Compilation.h"
#include "Error.h"
#include "Model.h"

#include <fstream>
#include <string>

#include <unistd.h>

using namespace std;

#define isWhitespace(c) (c==' ' || c=='\t' || c=='\n' || c==0)
#define isEndLine(c) (c=='\n' || c==0)
#define isString(c) (c=='\'' || c=='\"')

void parsePreCompilerDirective(string str, Config&config, Codestruct&codestruct)
{
  printf("Precomp %s\n", str.c_str());
}

vector <Page> Precompile(Config&config, Codestruct&codestruct)
{
  vector <Page> pages;

  if (config.debug)
    printf("Starting precompilation\n");

  //format source files
  //interpret pre-preprocessor directives
  for (size_t x=0; x<codestruct.sources.size(); ++x)
  {
    ifstream ifile(codestruct.sources[x]+".nrn");

    if (!ifile)
    {
      postError(ERR_FNF, -1, codestruct.sources[x]);
      continue;
    }

    if (config.debug)
      printf("Loading %s\n", codestruct.sources[x].c_str());

    while(!ifile.eof())
    {
      string line;
      string buffer;
      getline (ifile, line);

      int state = 0;
      size_t index;

      printf("%s\n", line.c_str());

      for (size_t y=0; y<=line.size(); ++y)
      {
        char c = line[y];

        sleep(1);

        switch (c)
        {
          printf("%c", c);
        }
      }
    }
  }

  return pages;
}
