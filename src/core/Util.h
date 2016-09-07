#ifndef UTIL
#define UTIL

#include <string>

using namespace std;

#define COLOR_BLACK   "\x1b[30m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"
#define COLOR_RESET   "\x1b[0m"

enum bm_operation{_bmSet, _bmClear, _bmToggle, _bmCheck};

int bitAction(int&, int, bm_operation);

//value to print, color code
void printc(string, const char *);
void printc(char, const char *);

string toJson();

#endif
