#ifndef NAV_LIBRARY_EXTENSION_H
#define NAV_LIBRARY_EXTENSION_H

#include <Nav_Api.h>
#include <Platform/Nav_Library.h>
#include <Types/Nav_Function_Pointer.h>
#include <Math/Nav_Value_Type.h>


#define NAV_LIBRARY_EXTENSION_ONLOAD_FUNCTION_NAME "Nav_Library_Extension_OnLoad"
#define NAV_LIBRARY_EXTENSION_ONUNLOAD_FUNCTION_NAME "Nav_Library_Extension_OnUnload"
#define NAV_LIBRARY_EXTENSION_GETFUNCTIONPOINTERSSTRUCTURESIZE_FUNCTION_NAME "Nav_Library_Extension_GetFunctionPointersStructureSize"

#define NAV_LIBRARY_EXTENSION_ONLOAD_FUNCTION() NAV_API void Nav_Library_Extension_OnLoad(Nav_Library* library, void* funcPtrsStruct)
#define NAV_LIBRARY_EXTENSION_ONUNLOAD_FUNCTION() NAV_API void Nav_Library_Extension_OnUnload()
#define NAV_LIBRARY_EXTENSION_GET_FUNCTION_POINTERS_SCTRUCTURE_SIZE_FUNCTION() NAV_API UInt64 Nav_Library_Extension_GetFunctionPointersStructureSize()

typedef NAV_FUNCTION_POINTER_DEFINE(void, Nav_Library_Extension_OnLoad_FunctionPointer, Nav_Library*, void*);
typedef NAV_FUNCTION_POINTER_DEFINE(void, Nav_Library_Extension_OnUnload_FunctionPointer, );
typedef NAV_FUNCTION_POINTER_DEFINE(UInt64, Nav_Library_Extension_GetFunctionPointersStructureSize_FunctionPointer, );

struct Nav_Library_ExtensionType
{
    Nav_Library* library;

    Nav_Library_Extension_OnLoad_FunctionPointer OnLoad;
    Nav_Library_Extension_OnUnload_FunctionPointer OnUnload;
    Nav_Library_Extension_GetFunctionPointersStructureSize_FunctionPointer GetFuncPtrsStructSize;

    UInt64 funcPtrsStructSize;
    void* funcPtrsStruct;
};

typedef struct Nav_Library_ExtensionType Nav_Library_Extension;

NAV_API Nav_Library_Extension Nav_Library_Extension_Load(char* libExtPath);
NAV_API void Nav_Library_Extension_Unload(Nav_Library_Extension libExt);

NAV_API Bool Nav_Library_Extension_IsValid(Nav_Library_Extension libExt);

#endif // NAV_LIBRARY_EXTENSION_H