

#include "signal.h"

using namespace std;

signalRegistry::signalRegistry(){
    _sigByteSize = 1;
}

int signalRegistry::getSignalSize(){
    return _signals.size();
}

signal signalRegistry::registerSignal(string name, string description){
    signal s;
    s.name = name;
    s.description = description;
    s.index = _signals.size();
    _signals.push_back(s);
    return s;
}

string signalRegistry::getSigName(int i){
    int size = _signals.size();
    if (i >= size)
        return "";
    return _signals[i].name;
}

string signalRegistry::getSigDesc(int i){
    int size = _signals.size();
    if (i >= size)
        return "";
    return _signals[i].description;
}