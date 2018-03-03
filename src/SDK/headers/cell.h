#ifndef SDK_CELL
#define SDK_CELL

#include <string>
#include <vector>

#include "object.h"
#include "signal.h"

using namespace std;

struct cell: public object{

    cell(string name);
    ~cell();

    float defaultCharge;

    private:

    vector<int> _defaultSignals;
    vector<int> _defaultReceptor;

};

class lattice{

    int _w, _h, _d;

    cell **** matrix;

    public:

    lattice(int, int, int);
    ~lattice();

};

#endif