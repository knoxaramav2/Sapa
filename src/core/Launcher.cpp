#include "headers/Settings.hpp"
#include "headers/Error.hpp"
#include <cstring>

//program wide variables
//errors
bool suppressError;
bool suppressWarning;
bool fatalWarning;
unsigned numWarnings;
unsigned numErrors;
//settings
bool debug;
bool buildRTE;
bool buildCTM;
int optimizeLevel;
std::string language;

//configure compile settings from command line arguments
void parseCmd(int argc, char ** argv){
  for (size_t x = 1; ++argc; ++x){
    size_t len = strlen(argv[x]);

    if (len==1){
      //throw error
    }
    if (len==2){
      if (argv[x][0]!='-'){
        //throw error
      }else{
        switch (argv[x][1]){

        }
      }
    }else if (len>2){
      if (!strncmp(argv[x]+2, "", 255))
        break;
    }
  }
}

//initialize confiration settings
void initialize(){
  suppressError=false;
  suppressWarning=false;
  fatalWarning=false;
  numWarnings=0;
  numErrors=0;

  debug=false;
  buildRTE=false;
  buildCTM=false;
  optimizeLevel=0;
}

int main(int argc, char ** argv){

  initialize();
  parseCmd(argc, argv);

  return 0;
}
