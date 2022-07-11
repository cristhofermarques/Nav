#define VK_USE_PLATFORM_WIN32_KHR 

#include <gfx/vk/nav_vk.h>
#include <gfx/vk/nav_vk_context_struct.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <platform/win32/win32_nav_window_struct.h>


char CreateVulkanSurface(VulkanContext* vkCtx, Window* wnd)
{
    if(&vkCtx->vkInstance == 0){return 0;}
    
    VkWin32SurfaceCreateInfoKHR vkWin32SurfCreateInfoKhr = {0};
    vkWin32SurfCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    vkWin32SurfCreateInfoKhr.hinstance = GetModuleHandle(0);
    vkWin32SurfCreateInfoKhr.hwnd = wnd->hWnd;

    VkResult vkRes = vkCreateWin32SurfaceKHR(vkCtx->vkInstance, &vkWin32SurfCreateInfoKhr, 0, &vkCtx->vkSurfaceKhr);

    if(vkRes != VK_SUCCESS){return 0;}

    {
        unsigned int gpuCount = 0U;
        VkPhysicalDevice vkPhysicalDevs[10] = {0};

        vkEnumeratePhysicalDevices(vkCtx->vkInstance, &gpuCount, 0);
        vkEnumeratePhysicalDevices(vkCtx->vkInstance, &gpuCount, vkPhysicalDevs);

        for(unsigned int i = 0; i < gpuCount; i++)
        {
            VkPhysicalDevice dev = vkPhysicalDevs[i];
            unsigned int queueFamilyCount = 0;

            VkQueueFamilyProperties queueProps[10];

            vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, 0);
            vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, &queueProps);

            for(unsigned int j = 0; j < queueFamilyCount; j++)
            {
                if(queueProps[j].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    *vkCtx->vkGfxIdx = &j;
                    break;
                }
            }
        }
    }

    return 1;
}