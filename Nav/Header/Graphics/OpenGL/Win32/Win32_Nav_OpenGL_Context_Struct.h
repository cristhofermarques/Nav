#ifndef WIN32_NAV_OPENGL_CONTEXT_STRUCT_H
#define WIN32_NAV_OPENGL_CONTEXT_STRUCT_H

#include <Graphics/OpenGL/Nav_OpenGL.h>
#include <Platform/Nav_Library.h>
#include <Windows.h>
#include <Graphics/OpenGL/GL/wglext.h>

struct NavOpenGLContextType
{
    NavLibrary* glLib;
    HGLRC hGlRc;
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
};

#endif // WIN32_NAV_OPENGL_CONTEXT_STRUCT_H