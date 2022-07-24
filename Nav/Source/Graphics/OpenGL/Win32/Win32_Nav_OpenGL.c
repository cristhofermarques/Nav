#include <Graphics/OpenGL/Nav_OpenGL.h>
#include <Graphics/OpenGL/Win32/Win32_Nav_OpenGL_Context_Struct.h>
#include <Platform/Win32/Win32_Nav_Window_Struct.h>
#include <Types/Nav_Value_Type.h>
#include <Nav_Debug.h>

UInt64 Nav_Graphics_OpenGL_GetContextSize()
{
    return (UInt64)sizeof(NavOpenGLContext); 
}

void* Nav_Graphics_OpenGL_GetFunctionPointer(NavOpenGLContext* glCtx, char* functionName)
{
    void* funcPtr = NullPtr;

    funcPtr = wglGetProcAddress(functionName);

    if(funcPtr == NullPtr)
    {
        if(glCtx != NullPtr)
        {
            if(glCtx->glLib == NullPtr)
            {
                glCtx->glLib = Nav_Library_GetLoaded("OpenGL32.dll");
            }

            if(glCtx->glLib != NullPtr)
            {
                funcPtr = Nav_Library_GetProcAddress(glCtx->glLib, functionName);
            }
        }
    }

    return funcPtr;
}

Bool Nav_Graphics_OpenGL_CreateContextForWindow(NavWindow* wnd, UInt8 glMajorVersion, UInt8 glMinorVersion, UInt8 colorBits, UInt8 depthBits, NavOpenGLContext* glCtx)
{
    NavWindow* dummyWnd = Nav_Window_Create("", 0, 0, NAV_WINDOW_STYLE_BORDERLESS);

    if(dummyWnd == NullPtr){return False;}

    PIXELFORMATDESCRIPTOR pxFmtDesc = NullStruct;
    pxFmtDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pxFmtDesc.nVersion = 1;
    pxFmtDesc.dwFlags = PFD_SUPPORT_OPENGL;
    pxFmtDesc.iPixelType = PFD_TYPE_RGBA;
    pxFmtDesc.cColorBits = colorBits;
    pxFmtDesc.cDepthBits = depthBits;
    pxFmtDesc.iLayerType = PFD_MAIN_PLANE;

    Int32 pxFmt = ChoosePixelFormat(dummyWnd->hDc, &pxFmtDesc);

    if(! pxFmt)
    {
        DEBUG_ERROR("Failed Create Dummy Window");
        Nav_Window_Destroy(dummyWnd);
        return False;
    }

    if(! SetPixelFormat(dummyWnd->hDc, pxFmt, &pxFmtDesc))
    {
        DEBUG_ERROR("Failed Set Pixel Format Dummy Window");
        Nav_Window_Destroy(dummyWnd);
        return False;
    }

    HGLRC hGlRc = wglCreateContext(dummyWnd->hDc);

    if(! hGlRc)
    {
        DEBUG_ERROR("Failed Create Dummy Context");
        Nav_Window_Destroy(dummyWnd);
        return False;
    }

    if(! wglMakeCurrent(dummyWnd->hDc, hGlRc))
    {
        DEBUG_ERROR("Failed Make Current Dummy Context");
        wglDeleteContext(hGlRc);
        Nav_Window_Destroy(dummyWnd);
        return False;
    }

    glCtx->wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    glCtx->wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if(glCtx->wglChoosePixelFormatARB == NullPtr || glCtx->wglCreateContextAttribsARB == NullPtr)
    {
        DEBUG_ERROR("Failed WGL Initial Function Pointers");
        wglMakeCurrent(0, 0);
        wglDeleteContext(hGlRc);
        Nav_Window_Destroy(dummyWnd);
        return False;
    }

    wglMakeCurrent(0, 0);
    wglDeleteContext(hGlRc);
    Nav_Window_Destroy(dummyWnd);

    Int32 pxFmtAttribs[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,        
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_COLOR_BITS_ARB, (Int32)colorBits,
        WGL_DEPTH_BITS_ARB, (Int32)depthBits,
        0
    };

    UInt32 pxFmtCount = 0;
    if(! glCtx->wglChoosePixelFormatARB(wnd->hDc, pxFmtAttribs, NullPtr, 1, &pxFmt, &pxFmtCount))
    {
        DEBUG_ERROR("Failed Choose Pixel Format");
        return False;
    }

    if(! SetPixelFormat(wnd->hDc, pxFmt, &pxFmtDesc))
    {
        DEBUG_ERROR("Failed Set Pixel Format");
        return False;
    }

    Int32 glCtxAttribs[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, glMajorVersion,
        WGL_CONTEXT_MINOR_VERSION_ARB, glMinorVersion,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB

#ifdef NAV_BUILD_MODE_DEBUG
        | WGL_CONTEXT_DEBUG_BIT_ARB
#endif
        , 0
    };

    hGlRc = glCtx->wglCreateContextAttribsARB(wnd->hDc, NullPtr, glCtxAttribs);

    if(! hGlRc)
    {
        DEBUG_ERROR("Failed Create Core Profile OpenGL Context");
        return False;
    }

    if(! wglMakeCurrent(wnd->hDc, hGlRc))
    {
        DEBUG_ERROR("Failed Make Current OpenGL Context");
        return False;
    }

    glCtx->hGlRc = hGlRc;
    glCtx->glLib = Nav_Library_GetLoaded("opengl32.dll");

    return True;
}

Bool Nav_Graphics_OpenGL_DestroyContext(NavOpenGLContext* glCtx)
{
    if(glCtx->hGlRc)
    {
        wglMakeCurrent(0, 0);
        wglDeleteContext(glCtx->hGlRc);
        return True;
    }


    if(glCtx->glLib != NullPtr)
    {
        Nav_Library_Unload(glCtx->glLib);
    }

    return False;
}

Bool Nav_Graphics_OpenGL_SwapBuffers(NavWindow* wnd)
{
    return SwapBuffers(wnd->hDc);
}