#ifndef SYS
#define SYS

#include <vector>
#include <string>

#include "Bio.hpp"

using namespace std;

//reference record table

struct version
{
	
	version();
	version(const string);

	short major;
	short minor;
	short patch;
};

union options
{
	struct
	{
		unsigned int prntOperation : 1;
		unsigned int prntErr : 1;
		unsigned int prntGenesis : 1;
		unsigned int prnt : 1;
	};
};

struct neuralTable
{
	std::vector <cell*> node;
};

class systemCore
{
	neuralTable table;
	options opts;
	version build;

public:
	systemCore(const string);
};

#endif