#include "Project.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>

Project::Project()
{
//  #ifdef __WINDOWS

//  #elif defined __LINUX
  char path[256];
  char dest[256];
  struct stat info;
  pid_t pid = getpid();
  sprintf(path, "/proc/%d/exe", pid);
  if (readlink(path, dest, 256) == -1)
    perror("readlink");
  else {
    printf(">>\t%s\n", dest);
  }
  //#endif

}
