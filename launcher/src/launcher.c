#include <Nav_Debug.h>
#include <Platform/Nav_Window.h>
#include <Graphics/OpenGL/Nav_OpenGL.h>
#include <Graphics/OpenGL/Nav_OpenGL_Functions.h>
#include <Types/Nav_Value_Type.h>
#include <Memory/Nav_Allocation.h>

int main(int argc, char** argv)
{
    NavWindow* wnd = Nav_Window_Create("nav", 600, 480, NAV_WINDOW_STYLE_BORDER_COMPLETE);

    NavOpenGLContext* glCtx = NAV_MEMORY_ALLOCATE(Nav_Graphics_OpenGL_GetContextSize());

    if(Nav_Graphics_OpenGL_CreateContextForWindow(wnd, 3, 0, 24, 32, glCtx))
    {
        if(Nav_Graphics_OpenGL_GetAllFunctionPointers(glCtx))
        {
            DEBUG_INFO("GL INITIALIZED");
        }
    }



    // VulkanContext* vkCtx = NullPtr;

    // if((vkCtx = CreateVulkanContext()) == NullPtr)
    // {
    //     DEBUG_ERROR("ctx");
    // }

    // if(CreateVulkanSurface(vkCtx, wnd))
    // {
    //     DEBUG_INFO("surf");
    // }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    while(Nav_Window_UpdateEvents(wnd))
    {   
        IntVector2 size = Nav_Window_GetClientSize(wnd);
        glViewport(0, 0, size.x, size.y);

        glClear(GL_COLOR_BUFFER_BIT);
        
        Sleep(10);

        Nav_Graphics_OpenGL_SwapBuffers(wnd);
        // Nav_Graphics_Vulkan_Render(vkCtx, Nav_Window_GetClientSize(wnd));
    }

    // DestroyVulkanContext(vkCtx);
    
    Nav_Graphics_OpenGL_DestroyContext(glCtx);
    NAV_MEMORY_DEALLOCATE(glCtx);
    Nav_Window_Destroy(wnd);

    return 0;
}
