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

std::pair<AIInterface, bool> dlib(void *handle)
{
  bool error = false;
  CTOR ctor = reinterpret_cast<CTOR>(dlsym(handle, "createLib"));
  if (ctor == nullptr)
  {
    error = true;
    std::cout << dlerror() << std::endl;
  }
  DTOR dtor = reinterpret_cast<DTOR>(dlsym(handle, "deleteLib"));
  if (dtor == nullptr)
  {
    error = true;
    std::cout << dlerror() << std::endl;
  }
  return (std::make_pair(AIInterface(handle, ctor, dtor), error));
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

std::pair<AIInterface, bool> dlib(HINSTANCE lhandle)
{
  bool error = false;
  CTOR ctor = reinterpret_cast<CTOR>(GetProcAddress(lhandle, "createLib"));
  if (ctor == nullptr)
  {
    error = true;
    std::cerr << "could not locate the function createLib" << std::endl;
  }
  DTOR dtor = reinterpret_cast<DTOR>(GetProcAddress(lhandle, "deleteLib"));
  if (dtor == nullptr)
  {
    error = true;
    std::cerr << "could not locate the function createLib" << std::endl;
  }
  return (std::make_pair(AIInterface(lhandle, ctor, dtor), error));
}

void dunload(HINSTANCE handle)
{
   if(FreeLibrary(handle)) {
        std::cout << dlerror() << std::endl;
   }
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
    if (std::string(file->d_name) != "." && std::string(file->d_name) != "..")
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
      auto li = dlib(dload(path));
      if (!li.second) { // NO ERROR
        libInterfaces_.push_back(li.first);
      }
    }
  }
}

int loadIa::getNbIa()
{
  return(libInterfaces_.size());
}

std::shared_ptr<IArtificialIntelligence> loadIa::getIa(int idx)
{
  if(idx < libInterfaces_.size() && idx > -1)
    return std::shared_ptr<IArtificialIntelligence>(libInterfaces_[idx].ctor(this->x, this->y, this->width, this->height), libInterfaces_[idx].dtor);
  else
    return nullptr;
}

loadIa::~loadIa()
{
  for (auto & li : libInterfaces_) {
    li.close();
  }
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
AIInterface::AIInterface(LibType ref, CTOR c, DTOR d): libref(ref), ctor(c), dtor(d) {}

void AIInterface::close() {
  dunload(libref);
}
