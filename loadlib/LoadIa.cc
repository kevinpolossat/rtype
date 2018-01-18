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

IArtificialIntelligence *dlib(void *handle,int width,int height, int x, int y)
{
  IArtificialIntelligence *(*ptr)(int, int, int, int);
  ptr = reinterpret_cast<IArtificialIntelligence *(*)(int, int, int, int)>(dlsym(handle, "createLib"));
  if (ptr == NULL)
  {
    std::cout << dlerror() << std::endl;
    return (0);
  }
    return(ptr(x, y, width, height));
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
    return NULL;
  }
  return(lhandle);
}

IArtificialIntelligence *dlib(HINSTANCE lhandle,int width,int height, int x , int y)
{
  type funci = (type)GetProcAddress(lhandle, "createLib");
    if (!funci)
    {
      std::cout << "could not locate the function" << std::endl;
      return NULL;
    }
  void *monster1 = funci(x, y, width, height);
  return(reinterpret_cast<IArtificialIntelligence*>(monster1));
}

#endif

std::vector<std::string> getcontents(std::string pathdir)
{
  DIR *folder;
  dirent *file;
  std::vector<std::string> names;
  if ((folder = opendir(pathdir.c_str())) == NULL)
    exit(0);
  while((file = readdir(folder)))
  {
    if (file->d_name != "." && file->d_name != "..")
    {
      //std::cout << file->d_name << '\n';
      names.push_back(file->d_name);
    }
  }
  if (closedir(folder) == -1)
    exit(0);
  return(names);
}

loadIa::loadIa(std::string pathdir, int width, int height)
{
  this->width = width;
  this->height = height;
  this->x = this->width - 1;
  this->y = rand() % this->height;
  for (auto it : getcontents(pathdir))
  {
    if (it != "." && it != "..")
    {
      std::cout << "it = " << it << std::endl;
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

IArtificialIntelligence *loadIa::getIa(int idx)
{
  if(idx < _ias.size() && idx > -1)
    return _ias[idx];
  else
    return (_ias[0]);
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
  return (0);
  */
}
