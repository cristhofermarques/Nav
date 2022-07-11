#ifndef WIN32_NAV_LIB_STRUCT_H
#define WIN32_NAV_LIB_STRUCT_H

#include <platform/nav_lib.h>

#define CLEAN_AND_MEAN
#include <windows.h>

struct LibraryType
{
    HMODULE hModule;
};

#endif