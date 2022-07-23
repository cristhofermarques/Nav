#include <Nav_Debug.h>
#include <Platform/Nav_Window.h>
#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    Nav_Window* wnd = Nav_Window_Create("nav", 600, 400);

    VulkanContext* vkCtx = NullPtr;

    if((vkCtx = CreateVulkanContext()) == NullPtr)
    {
        DEBUG_ERROR("ctx");
    }

    if(CreateVulkanSurface(vkCtx, wnd))
    {
        DEBUG_INFO("surf");
    }

    while(Nav_Window_UpdateEvents(wnd))
    {   
        Nav_Graphics_Vulkan_Render(vkCtx);
        //Sleep(10);
    }

    DestroyVulkanContext(vkCtx);
    
    Nav_Window_Destroy(wnd);

    return 0;
}
