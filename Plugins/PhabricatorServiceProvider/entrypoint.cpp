

#include <string>
#include "../../include/Dll.h"
#include "PhabricatorServiceProvider.h"

extern "C"
{
    const char __declspec(dllexport) * getId()
    {
        return ("Phabricator");
    }

    ServiceProvider::Interface __declspec(dllexport) * getInstance()
    {
        return (new ServiceProvider::Phabricator);
    }
}
