#include "KNX_String.h"

#include "object.h"

object::object(string name){
    this->name = name;
    this->hash = fnv1a_32((char *)name.c_str());
}