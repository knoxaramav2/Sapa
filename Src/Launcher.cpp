#include <string>
#include <cstdio>
#include <unistd.h>
#include <string.h>
#include <cstdlib>

#include "Bio.hpp"
#include "System.hpp"

#define VERSION (std::string) "1.0.0"

systemCore core(VERSION);

bool createNewProject()
{

	return true;
}

bool loadProject()
{

	return true;
}

void version()
{

}

void help()
{
	printf("\n\n");
	printf("-h		help\n");
	printf("-n FILE		new file\n");
	printf("-l FILE		load file\n");
	printf("-s		un-managed simulation\n");
	printf("\n\n");
}

int main(int argc, char**argv)
{
	std::string file;
	bool newProj = false;
	bool loadProj = false;
	bool hlp = false;
	bool sim = false;

	//parse cmd arguments
	for (int l = 1; l < argc; ++l)
	{
		printf("%s\n",argv[l]);

		if (argv[l][0] == '-')
		{
			if (strlen(argv[l]) != 2)
			{
				printf("Error: Invalid option: %s\n",argv[l]);
				exit(1);
			}

			switch (argv[l][1])
			{
			case 'h':
				hlp = true;
				break;
			case 'n':
				if (loadProj || sim)
				{
					printf("Error: -n cannot be used with -l or -s\n");
					exit(1);
				}
				if (l + 1 == argc)
				{
					printf("Error: -n must declare file name\n");
					exit(1);
				}
				newProj = true;
				file = argv[++argc];
				break;
			case 'l':
				if (newProj || sim)
				{
					printf("Error: -l cannot be used with -n or -s\n");
					exit(1);
				}
				if (l + 1 == argc)
				{
					printf("Error: -l must declare file name\n");
					exit(1);
				}
				loadProj = true;
				file = argv[++argc];
				break;
			case 's':
				if (newProj || loadProj)
				{
					printf("Error: -s cannot be used with -n or -l\n");
					exit(1);
				}
				sim = true;
				break;
			default:
				printf("Error: Invalid option\n");
				exit(1);
			}
		}
	}

	//execute commands

	if (hlp)
		help();
	if (newProj);
	else if (loadProj);
	else if (sim);


	return 0;
}