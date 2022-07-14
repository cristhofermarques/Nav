#include <Nav_Debug.h>
#include <Platform/Nav_Window.h>
#include <Extension/Nav_Library_Extension.h>
#include <Types/Nav_Function_Pointer.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    Nav_Window* wnd = Nav_Window_Create("nav", 600, 400);

    // VulkanContext* vkCtx = CreateVulkanContext();

    // if(CreateVulkanSurface(vkCtx, wnd))
    // {
    // }

    while(Nav_Window_UpdateEvents(wnd))
    {
        IntVector2 wndClientSize = Nav_Window_GetClientSize(wnd);
        DEBUG_LOG(DECIMAL_LOG_FORMAT DECIMAL_LOG_FORMAT, WHITE_CONSOLE_COLOR, wndClientSize.x, wndClientSize.y);

        IntVector2 wndPos = Nav_Window_GetPosition(wnd);
        DEBUG_LOG(DECIMAL_LOG_FORMAT DECIMAL_LOG_FORMAT, WHITE_CONSOLE_COLOR, wndPos.x, wndPos.y);
        
        Sleep(100);
    }

    // DestroyVulkanContext(vkCtx);
    
    Nav_Window_Destroy(wnd);

    return 0;
}
