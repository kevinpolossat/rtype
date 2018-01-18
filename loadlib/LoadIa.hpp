#include <vector>
#include <iostream>
#include <string>
#include "IArtificialIntelligence.hpp"
#include <sys/types.h>

#if defined (__linux__) || defined (__APPLE__)
  #include <dlfcn.h>
  #include <dirent.h>
#elif defined (_WIN32) || defined (_WIN64)
  #include <windows.h>
  #include "dirent.h"
typedef void *(*type)(int, int, int, int);
#endif

class loadIa
{
public:
  loadIa(std::string pathdir, int width, int height);
  ~loadIa();
  int  getNbIa();
  IArtificialIntelligence  *getIa(int idx);

private:
    int width;
    int height;
    int x;
    int y;
    std::vector<IArtificialIntelligence*> _ias;
};
