#ifndef ERROR
#define ERROR

#include <string>
#include <vector>

using namespace std;

extern int errCounter;
extern int wrnCounter;

//call per error
void postError(string line, string msg, unsigned errCode, int errIndex, char prntPolicy);
//report at end of compilation
void ErrorReport();
//true if able to continue operation
bool isFatal(bool);



//******************Error Codes*****************

//each allocated 2000 indexes
#define ERROR_LIM 0x7D0
#define WARN_LIM 0xFA0

//Errors
  //CMD 0x1 - 0x20
#define ERR_NO_SRC            0x1//missing source file (CNS)
#define ERR_MSS_CMD_PARAM     0x2//missing required CMD parameter
#define ERR_INV_OPT           0x3//invalid option

  //CNS 0x21 - 0x40
#define ERR_NO_LANG           0x21//language set
#define ERR_INV_CMD           0x22//invalid settings
#define ERR_CNS_404           0x23//CNS not found
#define ERR_EXPCT_COM         0x24//command statement missing
#define ERR_EXPCT_ARG         0x25//argument missing
#define ERR_INV_CNS_ARG       0x26//invalid CNS param

#define ERR_SETTING_REDEF     0x28//CNS system setting multiple values
#define ERR_MULT_COM          0x29//multiple command statements on line
#define ERR_NO_COM            0x2A//no command found
#define ERR_ARG_BFR_COM       0x2B//data found before command

//Registry0x41 - 0x60
#define ERR_REG_NCMP_TYPE     0x41//incompatible update type
#define ERR_RES_ENTRY         0x42//illegal access to reserved entry
#define ERR_REG_NOT_FOUND     0x43//registry entry not found

//Scanner 0x61-0x80
#define ERR_IMRT_NOT_FOUND    0x61//imported source not found

//Warnings
  //CMD 0x7D1 - 0x7E5
  //CNS 0x7E6 - 0x7F9
#define WRN_UNBOUND_QUOTE     0x7E6

#endif
