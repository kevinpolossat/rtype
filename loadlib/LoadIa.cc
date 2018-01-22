#include "LoadIa.hpp"

#if defined (__linux__) || defined (__APPLE__)
void *dload(const char *path_lib)
{
  void *handle;
  handle = dlopen(path_lib, RTLD_LAZY);
  if (!handle)
  {
    std::cout << dlerror() << std::endl;
    return(0);
  }
  return(handle);
}

std::shared_ptr<IArtificialIntelligence> dlib(void *handle, int width,int height, int x, int y)
{
  std::shared_ptr<IArtificialIntelligence> (*ptr)(int, int, int, int);
  ptr = reinterpret_cast<std::shared_ptr<IArtificialIntelligence> (*)(int, int, int, int)>(dlsym(handle, "createLib"));
  if (ptr == nullptr)
  {
    std::cout << dlerror() << std::endl;
    return (0);
  }
    return(ptr(x, y, width, height)->NewIA(x, y, width, height));
}

void dunload(void *handle)
{
  if(dlclose(handle))
    std::cout << dlerror() << std::endl;
}
#elif defined (_WIN32) || defined (_WIN64)

HINSTANCE dload(const char *path_lib)
{
	HINSTANCE lhandle;
	  lhandle= LoadLibrary(path_lib);
  std::cout << path_lib << std::endl;
  if (!lhandle)
  {
    std::cout << "could not load the dynamic library" << std::endl;
    return nullptr;
  }
  return(lhandle);
}

std::shared_ptr<IArtificialIntelligence> dlib(HINSTANCE lhandle,int width,int height, int x , int y)
{
  type funci = reinterpret_cast<type>(GetProcAddress(lhandle, "createLib"));
  if (!funci)
  {
    std::cerr << "could not locate the function" << std::endl;
    return nullptr;
  }
  void *monster1 = funci(x, y, width, height);
  return (reinterpret_cast<std::shared_ptr<IArtificialIntelligence>>(monster1));
}

#endif

std::vector<std::string> getcontents(std::string pathdir)
{
  DIR *folder;
  dirent *file;
  std::vector<std::string> names;

  if ((folder = opendir(pathdir.c_str())) == nullptr)
  {
    std::cerr << "ERROR OPENDIR" << std::endl;
    exit(0);
  }
  while((file = readdir(folder)))
  {
    if (file->d_name != "." && file->d_name != "..")
    {
      names.push_back(file->d_name);
    }
  }
  if (closedir(folder) == -1)
  {
    std::cerr << "ERROR CLOSEDIR" << std::endl;
    exit(0);
  }
  return(names);
}

loadIa::loadIa(std::string pathdir, int width, int height)
{
  this->width = width;
  this->height = height;
  this->x = this->width - 1;
  this->y = this->height / 2;

  for (auto it : getcontents(pathdir))
  {
    if (it != "." && it != "..")
    {
      std::string pathfile = pathdir + "/" + it;
      const char * path = pathfile.c_str();
      _ias.push_back(dlib(dload(path), width, height, x, y));
    }
  }
}

int loadIa::getNbIa()
{
  return(_ias.size());
}

std::shared_ptr<IArtificialIntelligence> loadIa::getIa(int idx)
{
  if(idx < _ias.size() && idx > -1)
    return _ias[idx]->NewIA(this->x, this->y, this->width, this->height);
  else
    return _ias[0]->NewIA(this->x, this->y, this->width, this->height);
}

loadIa::~loadIa()
{
  _ias.clear();
}

/*

int main(int ac, char ** av)
{
  #if defined (__linux__) || defined (__APPLE__)
  void *lhandle;
  #elif defined (_WIN32) || defined (_WIN64)
  HINSTANCE lhandle;
  #endif


  int width = 12;
  int height = 12;
  loadIa *ia = new loadIa("./Dll", width, height);
  for (int i = 0; i < ia->getNbIa(); i++)
      std::cout << ia->getIa(i)->getName() << std::endl;
  while (std::cin.get() != '\n');
  return (0);
} */
