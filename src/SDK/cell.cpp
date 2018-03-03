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

    matrix = new cell***[w];
    for(int x = 0; x < w; ++x){
        matrix[x] = new cell ** [h];
        for (int y = 0; y<h; ++y){
            matrix[x][y] = new cell*[d];
        }
    }
    
}

lattice::~lattice(){

}