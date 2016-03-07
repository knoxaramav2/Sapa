#include "Settings.hpp"

settings::settings()
{
  version="1.0.0";
  interlanguage="C";

  compileLevel=0;

  evolution=false;
  optomize=false;
  produceRTE=false;
  suppressWarnings=false;
  printProgress=false;
  debugMode=false;
}

settings::~settings()
{
  
}
