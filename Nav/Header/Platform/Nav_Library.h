#ifndef NAV_LIB_H
#define NAV_LIB_H

#include <nav_api.h>

struct Nav_LibraryType;
typedef struct Nav_LibraryType Nav_Library;

NAV_API Nav_Library* Nav_Library_Load(char* libPath);
NAV_API void Nav_Library_Unload(Nav_Library* lib);

NAV_API void* Nav_Library_GetProcAddress(Nav_Library* lib, char* procAddressName);

#endif