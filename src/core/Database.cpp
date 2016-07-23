#include "Database.h"

DBItem::DBItem(string name)
{
hash = FNV1a(name.c_str());
}
