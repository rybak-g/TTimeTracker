#ifndef DLMANAGER_HPP_
# define DLMANAGER_HPP_
# ifdef _WIN32
//#  include <filesystem>
# else
#  include <dirent.h>
# endif
# include <algorithm>
# include <sstream>
# include <exception>
# include <list>
# include <unordered_map>

# include "DlLoader.hpp"

template<typename _KEY_, class _INSTANCE_ = void>
class DlManager
{
public:
    typedef DlLoader<_INSTANCE_, _KEY_> Loader;
    typedef std::unordered_map<_KEY_, Loader *> PluginList;
    typedef std::list<_KEY_> KeyList;

private:
    PluginList _plugins;
    KeyList _keys;

public:
    DlManager() {}

    ~DlManager() {
        clear();
    }

    bool loadFromFile(std::string const& fileName) {
        Loader *tmp = new Loader;

        if (!tmp->load(fileName)) {
# ifdef _DEBUG
            qCritical() << "error loading [" << fileName.c_str() << "] : " << tmp->getLastError().c_str();
# endif
            delete tmp;
            return false;
        }
        if (_plugins.find(tmp->getId()) == _plugins.end()) {
            _plugins.emplace(tmp->getId(), tmp);
            _keys.push_back(tmp->getId());
# ifdef _DEBUG
            qInfo() << "loading [" << fileName.c_str() << "]";
# endif
        }
        else {
# ifdef _DEBUG
            qWarning() << "loading [" << fileName.c_str() << "] : library already loaded";
# endif
            delete tmp;
        }
        return true;
    }

    bool loadFromDir(const std::string & dirPath) {
        std::string str;

# ifdef _WIN32
        WIN32_FIND_DATAA fd;
        HANDLE handle = INVALID_HANDLE_VALUE;

        if (dirPath.length() > (MAX_PATH - 7)) {
#  ifdef _DEBUG
            qCritical() << "loading from directory [" << dirPath.c_str() << "] : path too long";
#  endif
            return (false);
        }
        str = dirPath + "/*.dll";
        if ((handle = FindFirstFileA(str.c_str(), &fd)) == INVALID_HANDLE_VALUE) {
#  ifdef _DEBUG
            qWarning() << "loading from directory [" << dirPath.c_str() << "] : no dynamic library found";
#  endif
            return (false);
        }
        str = dirPath + "/";
        do {
            this->loadFromFile((str + fd.cFileName).c_str());
        } while (FindNextFileA(handle, &fd) != 0);
        FindClose(handle);
        return (true);
# else
        DIR *d;
        struct dirent *dir;

        if (!(d = opendir(dirPath.c_str()))) {
#  ifdef _DEBUG
            std::cout << "Error loading from directory [" << dirPath << "] : cannot opendirectory" << std::endl;
#  endif
            return (false);
        }
        while ((dir = readdir(d)) != NULL) {
            str = dir->d_name;
#  ifndef _APPLE
            if (str.length() >= 4 && str.substr(str.length() - 3) == ".so")
#  else
            if (str.length() >= 7 && str.substr(str.length() - 6) == ".dylib")
#  endif
            {
                this->loadFromFile(dirPath + "/" + dir->d_name);
            }
        }
        closedir(d);
        return (true);
# endif
    }

    const Loader* getLoader(_KEY_ key) const {
        const typename PluginList::const_iterator &ite = _plugins.find(key);
        if (ite == _plugins.end())
            return nullptr;
        return ite->second;
    }

    template<typename T>
    T* getInstance(_KEY_ key, void *arg = nullptr) const {
        const typename PluginList::const_iterator &ite = _plugins.find(key);

        if (ite == _plugins.end()) {
# ifdef _DEBUG
            qCritical() << "error getting instance: not found";
# endif
            return nullptr;
        }
        return (reinterpret_cast<T *>(ite->second->getInstance(arg)));
    }

    const KeyList & getKeys() const {
        return this->_keys;
    }

    bool unload(_KEY_ const& key) {
        const typename PluginList::const_iterator &ite = _plugins.find(key);

        if (ite == _plugins.end())
            return (false);
        delete ite->second;
        _plugins.erase(ite);
        _keys.remove(key);
        return (true);
    }

    bool clear() {
        for (auto pair : _plugins) {
            delete pair.second;
        }
        _plugins.clear();
        _keys.clear();
        return true;
    }
};

#endif // !DLMANAGER_HPP_
