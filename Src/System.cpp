#include "System.hpp"

#include <cstdlib>
#include <string>

using namespace std;

version::version()
{
	major = 0;
	minor = 0;
	patch = 0;
}

version::version(const string b)
{
	int lvl = 0;
	
	unsigned lIndex = 0;
	for (unsigned l = 0; l < b.size(); ++l)
	{
		if (b[l] == '.' || l + 1 == b.size())
		{
			lIndex = l+1;
			switch (lvl)
			{
			case 0:
				major = (short) atoi(string(b.begin()+lIndex, b.begin()+l).c_str());
				break;
			case 1:
				minor = (short)atoi(string(b.begin() + lIndex, b.begin() + l).c_str());
				break;
			case 2:
				patch = (short)atoi(string(b.begin() + lIndex, b.begin() + l).c_str());
				break;
			}
		}
	}
}


systemCore::systemCore(const string b)
{
	build = version(b);
}