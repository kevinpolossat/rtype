#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "IArtificialIntelligence.hpp"
#include <sys/types.h>

#if defined (__linux__) || defined (__APPLE__)
  #include <dlfcn.h>
  #include <dirent.h>
#elif defined (_WIN32) || defined (_WIN64)
//  #include <windows.h>
  #include "dirent.h"
#endif

typedef std::shared_ptr<IArtificialIntelligence> (*type)(int, int, int, int);

class loadIa
{
public:
  loadIa(std::string pathdir, int width, int height);
  ~loadIa();
  int  getNbIa();
  std::shared_ptr<IArtificialIntelligence> getIa(int idx);

private:
    int width;
    int height;
    int x;
    int y;
    std::vector<std::shared_ptr<IArtificialIntelligence>> _ias;
};
