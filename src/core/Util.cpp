#include "Util.h"

#include <stdio.h>

int bitAction(int&val, int pos, bm_operation op){
  switch(op){
    case _bmSet:
      val |= 1 << pos;
      //printf("\n>Set %d<\n", val);
      return val;
    break;
    case _bmClear:
      val &= ~(1 << pos);
      //printf("\n>Clear %d<\n", val);
      return val;
    break;
    case _bmToggle:
      val ^= 1 << pos;
      //printf("\n>Toggle<\n");
      return val;
    break;
    case _bmCheck:
      return (val >> pos) & 1;
    break;
  }

  return val;
}

void printc(string line, const char * color){
  printf("%s%s" COLOR_RESET, color, line.c_str());
}

void printc(char c, const char * color){
  printf("%s%c" COLOR_RESET, color, c);
}
