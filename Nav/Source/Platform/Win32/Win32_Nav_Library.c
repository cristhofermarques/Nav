#include <Nav_Debug.h>
#include <Platform/Nav_Library.h>
#include <Platform/Win32/Win32_Nav_Library_Struct.h>
#include <windows.h>

Nav_Library* Nav_Library_Load(char* libPath)
{
    HMODULE hModule = LoadLibrary(libPath);

    if(hModule == NULL)
    {
        DEBUG_ERROR("failed to load library");
        return NULL;
    };

    Nav_Library* lib = malloc(sizeof(Nav_Library));

    if(lib == NULL)
    {
        DEBUG_ERROR("failed to alloc library memory");
        return NULL;
    };

    lib->hModule = hModule;

    return lib;
}

void Nav_Library_Unload(Nav_Library* lib)
{
    if(lib != NULL)
    {
        free(lib);
    }
}

void* Nav_Library_GetProcAddress(Nav_Library* lib, char* procAddressName)
{
    return GetProcAddress(lib->hModule, procAddressName);
}