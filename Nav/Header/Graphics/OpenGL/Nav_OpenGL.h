#ifndef NAV_OPENGL_H
#define NAV_OPENGL_H

#include <Nav_Api.h>
#include <Types/Nav_Value_Type.h>
#include <Graphics/OpenGL/GL/glcorearb.h>


struct NavOpenGLContextType;
typedef struct NavOpenGLContextType NavOpenGLContext;


NAV_API UInt64 Nav_Graphics_OpenGL_GetContextSize();

NAV_API Bool Nav_Graphics_OpenGL_GetFunctionPointer();
NAV_API Bool Nav_Graphics_OpenGL_CreateContext(UInt8 glMajorVersion, UInt8 glMinorVersion, UInt8 colorBits, UInt8 depthBits, NavOpenGLContext* glCtx);


#endif // NAV_OPENGL_H
