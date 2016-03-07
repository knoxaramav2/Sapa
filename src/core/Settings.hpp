#ifndef SETTINGS
#define SETTINGS

/*
Defines system settings and toggles
*/

#include <string>
#include <vector>

using namespace std;

struct settings
{
settings();
~settings();

//paths
string outputPath;
string projName;
string version;
string interlanguage;
string inputFile;//input cns file

//limits
int compileLevel;//maximum compiler step : 0=none 1=analysis 2=compile to connectome/ RTE source

//toggles
bool evolution : 2;
bool optomize : 2;
bool produceRTE : 2;//generates a runtime executable as well as a connectome
bool produceCTM : 2;//produce connectome file
bool suppressWarnings : 2;
bool printProgress : 2;
bool debugMode : 2;

};

#endif
