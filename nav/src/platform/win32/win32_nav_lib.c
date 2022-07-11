#include <nav_debug.h>
#include <platform/nav_lib.h>
#include <platform/win32/win32_nav_lib_struct.h>
#include <windows.h>

Library* NavLoadLibrary(char* libPath)
{
    HMODULE hModule = LoadLibrary(libPath);

    if(hModule == NULL)
    {
        DEBUG_ERROR("failed to load library");
        return NULL;
    };

    Library* lib = malloc(sizeof(Library));

    if(lib == NULL)
    {
        DEBUG_ERROR("failed to alloc library memory");
        return NULL;
    };

    lib->hModule = hModule;

    return lib;
}

void NavUnloadLibrary(Library* lib)
{
    if(lib != NULL)
    {
        free(lib);
    }
}

void* GetLibraryProcAddress(Library* lib, char* procAddressName)
{
    return GetProcAddress(lib->hModule, procAddressName);
}