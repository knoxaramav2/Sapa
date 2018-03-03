#ifndef SDK_OBJECT
#define SDK_OBJECT

#include <string>

using namespace std;

struct object{
    string name;
    unsigned long hash;
    unsigned id;

    object(string name);
};

#endif