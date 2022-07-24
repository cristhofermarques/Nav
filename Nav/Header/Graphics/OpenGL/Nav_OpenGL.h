#ifndef NAV_OPENGL_H
#define NAV_OPENGL_H

#include <Nav_Api.h>
#include <Types/Nav_Value_Type.h>
#include <Graphics/OpenGL/GL/glcorearb.h>
#include <Platform/Nav_Window.h>


struct NavOpenGLContextType;
typedef struct NavOpenGLContextType NavOpenGLContext;


NAV_API UInt64 Nav_Graphics_OpenGL_GetContextSize();

NAV_API void* Nav_Graphics_OpenGL_GetFunctionPointer(NavOpenGLContext* glCtx, char* functionName);

NAV_API Bool Nav_Graphics_OpenGL_CreateContextForWindow(NavWindow* wnd, UInt8 glMajorVersion, UInt8 glMinorVersion, UInt8 colorBits, UInt8 depthBits, NavOpenGLContext* glCtx);
NAV_API Bool Nav_Graphics_OpenGL_DestroyContext(NavOpenGLContext* glCtx);
NAV_API Bool Nav_Graphics_OpenGL_SwapBuffers(NavWindow* wnd);


#endif // NAV_OPENGL_H
