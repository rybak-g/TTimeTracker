#ifndef DLL_HH_
# define DLL_HH_
# ifndef _WIN32
#  define __declspec(dllexport)
# endif

namespace DL
{
    enum Type
    {
        ServiceProviderPlugin
    };
}

#endif // !DLL_HH_
