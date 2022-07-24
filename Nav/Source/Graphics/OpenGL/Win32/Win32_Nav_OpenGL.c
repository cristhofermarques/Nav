#include <Graphics/OpenGL/Nav_OpenGL.h>
#include <Graphics/OpenGL/Win32/Win32_Nav_OpenGL_Context_Struct.h>
#include <Platform/Nav_Window.h>
#include <Platform/Win32/Win32_Nav_Window_Struct.h>

UInt64 Nav_Graphics_OpenGL_GetContextSize()
{
    return sizeof(NavOpenGLContext);
}

Bool Nav_Graphics_OpenGL_CreateContext(UInt8 glMajorVersion, UInt8 glMinorVersion, UInt8 colorBits, UInt8 depthBits, NavOpenGLContext* pGlCtx)
{
    NavWindow* dummyWnd = Nav_Window_Create("", 0, 0);

    PIXELFORMATDESCRIPTOR pxFmtDesc = NullStruct;
    pxFmtDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pxFmtDesc.nVersion = 1;

    ChoosePixelFormat(dummyWnd->hDc);
}