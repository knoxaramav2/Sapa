#include "Compilation.hpp"
#include "Error.hpp"

#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

void writeDivider(ofstream & writer, string regName)
{

  size_t rd_len = 30;
  size_t ri_len = regName.size();

  rd_len -= (ri_len/2);
  rd_len /= 2;

  string wline;

  for (size_t x=0; x<rd_len; ++x)
    wline+='#';

  wline+=regName;

  for (size_t x=0; x<rd_len; ++x)
    wline+='#';

  writer<<endl<<endl<<"/*"<<wline<<"*/"<<endl<<endl;

}

void writeHeader(ofstream & writer)
{
  writer<<"#include <stdio.h>\n";
  writer<<"#include <stdlib.h>\n";
  writer<<"#include <math.h>\n";

  //write defines
}

void writeEntry(ofstream & writer)
{
  writer<<"int main(int argc, char ** argv){\n";
  writer<<"printf(\"Loading system...\\n\");\n";
  writer<<"printf(\"<C>\\n\");\n";

}

void writeClosing(ofstream & writer)
{
  writer<<"return 0;\n";
  writer<<"}\n";
}

void compile_C(Project & prj)
{

  ofstream writer(prj.formatPath(prj.projName, ".c"));

  if (!writer)
  {
    postError(prj.formatPath(prj.projName, ".c"), "", ERR_FWRITE_FAIL, -1, prj.noErr<<1);
    return;
  }

  writeDivider(writer, "HEADER");
  writeHeader(writer);
  writeDivider(writer, "DECLARATIONS");
  writeDivider(writer, "ENTRY");
  writeEntry(writer);
  writeDivider(writer, "INITILIZATION");
  writeDivider(writer, "START SIMULATION");
  writeDivider(writer, "SHUTDOWN");
  writeClosing(writer);

  writer.close();

}
