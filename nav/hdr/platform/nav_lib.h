#ifndef NAV_LIB_H
#define NAV_LIB_H

#include <nav_api.h>

struct LibraryType;
typedef struct LibraryType Library;

NAV_API Library* NavLoadLibrary(char* libPath);
NAV_API void NavUnloadLibrary(Library* lib);

NAV_API void* GetLibraryProcAddress(Library* lib, char* procAddressName);

#endif