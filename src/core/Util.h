#ifndef UTIL
#define UTIL

enum bm_operation{_bmSet, _bmClear, _bmToggle, _bmCheck};

int bitAction(int&, int, bm_operation);

#endif
