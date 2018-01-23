#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <sys/types.h>
#include "IArtificialIntelligence.hpp"

#if defined (__linux__) || defined (__APPLE__)
  #include <dlfcn.h>
  #include <dirent.h>
using LibType = void *;
#elif defined (_WIN32) || defined (_WIN64)
  #include <windows.h>
  #include "dirent.h"
using LibType = HINSTANCE;
#endif

using CTOR = IArtificialIntelligence* (*)(int, int, int, int);
using DTOR = void (*)(IArtificialIntelligence *);

struct AIInterface {
    AIInterface(LibType ref, CTOR c, DTOR d);
    void close();
    LibType libref;
    CTOR ctor;
    DTOR dtor;
};

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
    std::vector<AIInterface> libInterfaces_;
};
