#ifndef ERROR
#define ERROR

#include <string>

using namespace std;

#define MIN_WARNC  1
#define MAX_WARNC  10000
#define MIN_ERRC   10001
#define MAX_ERRC   20000

extern bool suppressError;
extern bool suppressWarning;
extern bool fatalWarning;
extern unsigned numWarnings;
extern unsigned numErrors;

//Error code, index, comment
void postError(unsigned, int, string);

bool isFatal();

#endif
