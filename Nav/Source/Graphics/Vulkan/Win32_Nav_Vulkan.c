#define VK_USE_PLATFORM_WIN32_KHR 

#include <Nav_Debug.h>
#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <Graphics/Vulkan/Nav_Vulkan_Context_Struct.h>
#include <Platform/Win32/Win32_Nav_Window_Struct.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#define VK_PHYSICAL_DEVICE_ARRAY_LENGTH 10
#define VK_QUEUE_FAMILY_PROPERTIES_ARRAY_LENGTH 10

char CreateVulkanSurface(VulkanContext* vkCtx, Nav_Window* wnd)
{
    if(&vkCtx->vkInstance == 0){return 0;}
    
    VkWin32SurfaceCreateInfoKHR vkWin32SurfCreateInfoKhr = {0};
    vkWin32SurfCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    vkWin32SurfCreateInfoKhr.hinstance = GetModuleHandle(0);
    vkWin32SurfCreateInfoKhr.hwnd = wnd->hWnd;

    VkResult vkRes = vkCreateWin32SurfaceKHR(vkCtx->vkInstance, &vkWin32SurfCreateInfoKhr, 0, &vkCtx->vkSurfaceKhr);

    if(vkRes != VK_SUCCESS){return 0;}
    {
        unsigned int devCount = 0U;
        VkPhysicalDevice vkPhysicalDevs[VK_PHYSICAL_DEVICE_ARRAY_LENGTH] = {0};

        VK_CHECK_FAIL_TO_RETURN_FUNC(vkEnumeratePhysicalDevices(vkCtx->vkInstance, &devCount, 0), DEBUG_ERROR("fail vulkan enumarate physical devices 0"));
        VK_CHECK_FAIL_TO_RETURN_FUNC(vkEnumeratePhysicalDevices(vkCtx->vkInstance, &devCount, vkPhysicalDevs), DEBUG_ERROR("fail vulkan enumarate physical devices 1"));

        for(unsigned int devIdx = 0; devIdx < devCount; devIdx++)
        {
            VkPhysicalDevice dev = vkPhysicalDevs[devIdx];

            unsigned int queueFamilyCount = 0;
            VkQueueFamilyProperties queueProps[VK_QUEUE_FAMILY_PROPERTIES_ARRAY_LENGTH];

            vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, 0);
            vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, &queueProps);

            for(unsigned int queueFamilyIdx = 0; queueFamilyIdx < queueFamilyCount; queueFamilyIdx++)
            {
                if(queueProps[queueFamilyIdx].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    VkBool32 devSurfaceSuport = VK_FALSE;

                    VK_CHECK_FAIL_TO_RETURN_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR(dev, queueFamilyIdx, vkCtx->vkSurfaceKhr, & devSurfaceSuport), DEBUG_ERROR("fail vulkan get physical device surface surport"));

                    if(devSurfaceSuport)
                    {
                        vkCtx->vkGfxIdx = queueFamilyIdx;
                        vkCtx->vkPhysicalDev = dev;
                        break;
                    }
                }
            }
        }

        {
            float queuePriority = 1.0f;

            VkDeviceQueueCreateInfo vkDevQueueCreateInfo = {0};
            vkDevQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            vkDevQueueCreateInfo.queueFamilyIndex = vkCtx->vkGfxIdx;
            vkDevQueueCreateInfo.pQueuePriorities = &queuePriority;

            char* extensions[] = 
            {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            VkDeviceCreateInfo vkDevCreateInfo = {0};
            vkDevCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            vkDevCreateInfo.pQueueCreateInfos = &vkDevQueueCreateInfo;
            vkDevCreateInfo.ppEnabledExtensionNames = extensions;
            vkDevCreateInfo.enabledExtensionCount = 1;

            VK_CHECK_FAIL_TO_RETURN_FUNC(vkCreateDevice(vkCtx->vkPhysicalDev, &vkDevCreateInfo, 0, &vkCtx->vkDev), DEBUG_ERROR("fail vulkan create device"))
        }

        {
            VkSwapchainCreateInfoKHR vkSwapchainCreateInfoKhr = {0};
            vkSwapchainCreateInfoKhr.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            vkSwapchainCreateInfoKhr.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            vkSwapchainCreateInfoKhr.surface = vkCtx->vkSurfaceKhr;

            VK_CHECK_FAIL_TO_RETURN_FUNC(vkCreateSwapchainKHR(vkCtx->vkDev, &vkSwapchainCreateInfoKhr, 0, vkCtx->vkSwapchainKhr), DEBUG_ERROR("fail vulkan create swap chain"))
        }
    }

    return 1;
}