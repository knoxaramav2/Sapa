#include "cell.h"

cell::cell(string name) : object(name){
    defaultCharge = 0;
}

cell::~cell(){

}

lattice::lattice(int w, int h, int d){
    _w = w;
    _h = h;
    _d = d;

    matrix = new cell**[w];
    
}

lattice::~lattice(){

}