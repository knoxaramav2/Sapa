#include "KNX_Hash.h"

#include "object.h"

object::object(string name){
    this->name = name;
    this->hash = FNV_1a_32(name.c_str());
}