#ifndef NAV_LIBRARY_H
#define NAV_LIBRARY_H

#include <Nav_Api.h>

struct NavLibraryType;
typedef struct NavLibraryType NavLibrary;

NAV_API NavLibrary* Nav_Library_Load(char* libPath);
NAV_API NavLibrary* Nav_Library_GetLoaded(char* libPath);
NAV_API void Nav_Library_Unload(NavLibrary* lib);

NAV_API void* Nav_Library_GetProcAddress(NavLibrary* lib, char* procAddressName);

#endif