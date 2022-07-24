#include <Extension/Nav_Library_Extension.h>
#include <Memory/Nav_Allocation.h>
#include <Nav_Debug.h>

NavLibraryExtension Nav_Library_Extension_Load(char* libExtPath)
{
    NavLibraryExtension libExt = NullStruct;

    NavLibrary* lib = Nav_Library_Load(libExtPath);

    if(lib == NullPtr)
    {
        DEBUG_ERROR("failed to load library");
        return libExt;
    }

    Nav_Library_Extension_OnLoad_FunctionPointer libExtOnLoad = (Nav_Library_Extension_OnLoad_FunctionPointer)Nav_Library_GetProcAddress(lib, NAV_LIBRARY_EXTENSION_ONLOAD_FUNCTION_NAME);
    Nav_Library_Extension_OnUnload_FunctionPointer libExtOnUnload = (Nav_Library_Extension_OnUnload_FunctionPointer)Nav_Library_GetProcAddress(lib, NAV_LIBRARY_EXTENSION_ONUNLOAD_FUNCTION_NAME);
    Nav_Library_Extension_GetFunctionPointersStructureSize_FunctionPointer libExtGetFuncPtrsStructSize = (Nav_Library_Extension_GetFunctionPointersStructureSize_FunctionPointer)Nav_Library_GetProcAddress(lib, NAV_LIBRARY_EXTENSION_GETFUNCTIONPOINTERSSTRUCTURESIZE_FUNCTION_NAME);

    if(libExtOnLoad == NullPtr || libExtOnUnload == NullPtr || libExtGetFuncPtrsStructSize == NullPtr)
    {
        DEBUG_ERROR("failed to get library extensions functions pointers");
        Nav_Library_Unload(lib);
        return;
    }

    UInt64 libExtFuncPtrsStructSize = NAV_FUNCTION_POINTER_CALL(libExtGetFuncPtrsStructSize, );

    if(libExtFuncPtrsStructSize == 0)
    {
        DEBUG_ERROR("failed to get library extensions functions pointers structure size");
        Nav_Library_Unload(lib);
        return;
    }
    

    void* libExtFuncPtrsStruct = NAV_MEMORY_ALLOCATE(libExtFuncPtrsStructSize);

    if(libExtFuncPtrsStruct == NullPtr)
    {
        DEBUG_ERROR("failed to allocate library extensions functions pointers structure memory");
        Nav_Library_Unload(lib);
        return;
    }

    NAV_FUNCTION_POINTER_CALL(libExtOnLoad, lib, libExtFuncPtrsStruct);

    libExt.library = lib;
    libExt.OnLoad = libExtOnLoad;
    libExt.OnUnload = libExtOnUnload;
    libExt.GetFuncPtrsStructSize = libExtGetFuncPtrsStructSize;
    libExt.funcPtrsStructSize = libExtFuncPtrsStructSize;
    libExt.funcPtrsStruct = libExtFuncPtrsStruct;

    return libExt;
}

void Nav_Library_Extension_Unload(NavLibraryExtension libExt)
{
    if(!Nav_Library_Extension_IsValid(libExt)){return;}

    NAV_FUNCTION_POINTER_CALL(libExt.OnUnload,);

    Nav_Library_Unload(libExt.library);
}

Bool Nav_Library_Extension_IsValid(NavLibraryExtension libExt)
{
    return libExt.library != NullPtr && libExt.OnLoad != NullPtr && libExt.OnUnload != NullPtr && libExt.GetFuncPtrsStructSize != NullPtr && libExt.funcPtrsStructSize != 0 && libExt.funcPtrsStruct != NullPtr;
}
