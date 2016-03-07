#include "Compiler.hpp"
#include "Settings.hpp"
#include "Registry.hpp"

#include <string>
#include <fstream>

using namespace std;

bool loadCNS(settings&stt, fileRegistry&fReg)
{
  ifstream cnsFile(stt.inputFile);

  if (!cnsFile)
    return false;

  enum rMode{NA,depend, config};

  return true;
}
