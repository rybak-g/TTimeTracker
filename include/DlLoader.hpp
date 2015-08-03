//
//
//
//
//
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_
# include <stdexcept>
# include <string>
# include <iostream>
# ifdef _WIN32
#  include <Windows.h>
#  include <Winbase.h>
typedef HINSTANCE LibraryHandler;
# else
#  include <dlfcn.h>
typedef void * LibraryHandler;
#endif

template<class _T_, typename _KEY_>
class DlLoader
{
public:
    typedef _KEY_ (*IdGetter)();
    typedef _T_ *(*InstanceGetter)(void *arg);

private:
    _KEY_ id;
    std::string fileName;
    std::string instGetterStr;
    std::string idGetterStr;
    std::string lastError;
    InstanceGetter instanceGetter;
    IdGetter idGetter;
    LibraryHandler handler;

    void unload()
    {
#ifdef _WIN32
        if (!FreeLibrary(this->handler))
#else
        if (dlclose(this->handler))
#endif
        {
#ifdef _DEBUG
            std::cerr << ("Error unloading library: " + fileName) << std::endl;
#endif
        }
    }

public:
    DlLoader() { }

    ~DlLoader() {
        if (this->handler) {
            this->unload();
        }
    }

    bool load(std::string const & path, const std::string& id = "getId", const std::string& instance = "getInstance") {
        fileName = path;
        instGetterStr = instance;
        idGetterStr = id;

#ifdef _WIN32
        this->handler = LoadLibraryA(path.c_str());
#else
        this->handler = dlopen(path.c_str(), RTLD_LAZY);
#endif
        if (!(this->handler)) {
            lastError = "loading failure";
            return false;
        }
#ifdef _WIN32
        this->idGetter = (IdGetter)(GetProcAddress(this->handler, idGetterStr.c_str()));
        this->instanceGetter = (InstanceGetter)(GetProcAddress(this->handler, instGetterStr.c_str()));
#else
        this->idGetter = (IdGetter)(dlsym(this->handler, idGetterStr.c_str()));
        this->instanceGetter = (InstanceGetter)(dlsym(this->handler, instGetterStr.c_str()));
#endif
        if (!idGetter || !instanceGetter) {
            this->unload();
            lastError = "cannot find the entry point ";
#ifndef _WIN32
            lastError += " : ";
            lastError += dlerror();
#endif
            return false;
        }
        this->id = idGetter();
        return true;
    }

    const _KEY_ getId() const {
        return this->id;
    }

    _T_ * getInstance(void *arg) const {
        if (instanceGetter)
            return instanceGetter(arg);
        return nullptr;
    }

    const std::string & getLastError() const {
        return lastError;
    }
};

#endif // !DLLOADER_HPP_
