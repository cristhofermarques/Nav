#include <gfx/vk/nav_vk.h>
#include <nav_debug.h>

int main(int argc, char** argv)
{
    VulkanContext* vkCtx = CreateVulkanContext();

    if(vkCtx != 0){DEBUG_INFO("no error at instance");}

    Window* wnd = NavCreateWindow("nav", 600, 400);

    char res = CreateVulkanSurface(vkCtx, wnd);

    if(res){
        DEBUG_INFO("yesss");
    }

    DestroyVulkanContext(vkCtx);

    NavDestroyWindow(wnd);

    return 0;
}
