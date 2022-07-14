#ifndef WIN32_NAV_LIB_STRUCT_H
#define WIN32_NAV_LIB_STRUCT_H

#include <Platform/Nav_Library.h>

#define CLEAN_AND_MEAN
#include <windows.h>

struct Nav_LibraryType
{
    HMODULE hModule;
};

#endif