#define VK_USE_PLATFORM_WIN32_KHR 

#include <Nav_Debug.h>
#include <Memory/Nav_Allocation.h>
#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <Graphics/Vulkan/Nav_Vulkan_Context_Struct.h>
#include <Platform/Win32/Win32_Nav_Window_Struct.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#define VK_PHYSICAL_DEVICE_ARRAY_LENGTH 10
#define VK_QUEUE_FAMILY_PROPERTIES_ARRAY_LENGTH 10

#define False 0x00
#define True 0xff

Bool Nav_Graphics_Vulkan_CreateSurface(VulkanContext* vkCtx, Nav_Window* wnd)
{
    if(vkCtx == NullPtr){return False;}

    VkWin32SurfaceCreateInfoKHR vkWin32SurfCreateInfoKhr = NullStruct;
    vkWin32SurfCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    vkWin32SurfCreateInfoKhr.hinstance = GetModuleHandle(NullPtr);
    vkWin32SurfCreateInfoKhr.hwnd = wnd->hWnd;

    return vkCreateWin32SurfaceKHR(vkCtx->vkInstance, &vkWin32SurfCreateInfoKhr, NullPtr, &vkCtx->vkSurfaceKhr) == VK_SUCCESS;
}

Bool Nav_Graphics_Vulkan_SelectPhysicalDevice(VulkanContext* vkCtx)
{
    if(vkCtx == NullPtr){return False;}

    UInt32 physicalDevCount = 0;
    if(vkEnumeratePhysicalDevices(vkCtx->vkInstance, &physicalDevCount, NullPtr) == VK_SUCCESS)
    {
        VkPhysicalDevice* physicalDevs = NAV_MEMORY_ALLOCATE(sizeof(VkPhysicalDevice) * physicalDevCount);

        if(physicalDevs != NullPtr)
        {
            if(vkEnumeratePhysicalDevices(vkCtx->vkInstance, &physicalDevCount, physicalDevs) == VK_SUCCESS)
            {
                for(UInt32 physicalDevIdx = 0; physicalDevIdx < physicalDevCount; physicalDevIdx++)
                {
                    VkPhysicalDevice physicalDev = physicalDevs[physicalDevIdx];


                    VkPhysicalDeviceProperties physicalDevProps = NullStruct;
                    VkPhysicalDeviceFeatures physicalDevFeatures = NullStruct;

                    vkGetPhysicalDeviceProperties(physicalDev, &physicalDevProps);
                    vkGetPhysicalDeviceFeatures(physicalDev, &physicalDevFeatures);

                    UInt32 queueFamilyCount = 0;
                    vkGetPhysicalDeviceQueueFamilyProperties(physicalDev, &queueFamilyCount, NullPtr);

                    if(queueFamilyCount != 0)
                    {
                        VkQueueFamilyProperties* queueFamilyProps = NAV_MEMORY_ALLOCATE(sizeof(VkQueueFamilyProperties) * queueFamilyCount);

                        if(queueFamilyProps != NullPtr)
                        {
                            vkGetPhysicalDeviceQueueFamilyProperties(physicalDev, &queueFamilyCount, queueFamilyProps);

                            for(UInt32 queueFamilyPropIdx = 0; queueFamilyPropIdx < queueFamilyCount; queueFamilyPropIdx++)
                            {
                                VkQueueFamilyProperties queueFamilyProp = queueFamilyProps[queueFamilyPropIdx];

                                if(queueFamilyProp.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                                {
                                    VkBool32 physicalDevSuportSurface = VK_FALSE;
                                    if(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDev, queueFamilyPropIdx, vkCtx->vkSurfaceKhr, &physicalDevSuportSurface) == VK_SUCCESS && physicalDevSuportSurface)
                                    {
                                        vkCtx->vkGfxIdx = queueFamilyPropIdx;
                                        vkCtx->vkPhysicalDev = physicalDev;
                                        break;
                                    }
                                }
                            }

                            NAV_MEMORY_DEALLOCATE(queueFamilyProps);
                        }
                    }
                }
            }

            NAV_MEMORY_DEALLOCATE(physicalDevs);
        }
    }

    return True;
}

Bool Nav_Graphics_Vulkan_CreateDevice(VulkanContext* vkCtx, float queuePriority)
{
    if(vkCtx == NullPtr){return False;}

    VkDeviceQueueCreateInfo vkDevQueueCreateInfo = NullStruct;
    vkDevQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkDevQueueCreateInfo.queueFamilyIndex = vkCtx->vkGfxIdx;
    vkDevQueueCreateInfo.pQueuePriorities = &queuePriority;
    vkDevQueueCreateInfo.queueCount = 1;

    char* extensions[] = 
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkDeviceCreateInfo vkDevCreateInfo = NullStruct;
    vkDevCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vkDevCreateInfo.pQueueCreateInfos = &vkDevQueueCreateInfo;
    vkDevCreateInfo.queueCreateInfoCount = 1;
    vkDevCreateInfo.ppEnabledExtensionNames = extensions;
    vkDevCreateInfo.enabledExtensionCount = 1;

    if(vkCreateDevice(vkCtx->vkPhysicalDev, &vkDevCreateInfo, NullPtr, &vkCtx->vkDev) != VK_SUCCESS)
    {
        DEBUG_ERROR("fail vulkan create device")
        return False;
    }    

    vkGetDeviceQueue(vkCtx->vkDev, vkCtx->vkGfxIdx, 0, &vkCtx->vkQueue);

    return True;
}

char CreateVulkanSurface(VulkanContext* vkCtx, Nav_Window* wnd)
{
    if(&vkCtx->vkInstance == 0){return 0;}
    
    VkWin32SurfaceCreateInfoKHR vkWin32SurfCreateInfoKhr = {0};
    vkWin32SurfCreateInfoKhr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    vkWin32SurfCreateInfoKhr.hinstance = GetModuleHandle(0);
    vkWin32SurfCreateInfoKhr.hwnd = wnd->hWnd;

    VkResult vkRes = vkCreateWin32SurfaceKHR(vkCtx->vkInstance, &vkWin32SurfCreateInfoKhr, 0, &vkCtx->vkSurfaceKhr);


    if(! Nav_Graphics_Vulkan_CreateSurface(vkCtx, wnd)){return False;}
    if(! Nav_Graphics_Vulkan_SelectPhysicalDevice(vkCtx)){return False;}
    if(! Nav_Graphics_Vulkan_CreateDevice(vkCtx, 1.0f)){return False;}

    {        

        {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(vkCtx->vkPhysicalDev, &props);

            DEBUG_LOG(STRING_LOG_FORMAT, GREEN_CONSOLE_COLOR, props.deviceName);

            UInt32 surfFmtCount = 0;
            VkSurfaceFormatKHR vkSurfFmts[16] = {0};

            if(vkGetPhysicalDeviceSurfaceFormatsKHR(vkCtx->vkPhysicalDev, vkCtx->vkSurfaceKhr, &surfFmtCount, NullPtr) == VK_SUCCESS &&
            vkGetPhysicalDeviceSurfaceFormatsKHR(vkCtx->vkPhysicalDev, vkCtx->vkSurfaceKhr, &surfFmtCount, &vkSurfFmts)  == VK_SUCCESS)
            {        
                DEBUG_LOG(STRING_LOG_FORMAT DECIMAL_LOG_FORMAT, GREEN_CONSOLE_COLOR, "got surface format ", surfFmtCount);

                for(UInt32 surfFmtIdx = 0U; surfFmtIdx < surfFmtCount; surfFmtIdx++)
                {
                    VkSurfaceFormatKHR surfFmt = vkSurfFmts[surfFmtIdx];
                    DEBUG_LOG(DECIMAL_LOG_FORMAT , GREEN_CONSOLE_COLOR, surfFmt.format);

                    if(surfFmt.format == VK_FORMAT_B8G8R8A8_SRGB)
                    {
                        vkCtx->vkSurfFormat = surfFmt;
                        DEBUG_INFO("YES");
                        break;
                    }
                }

            }

            UInt32 presentModeCount = 0U;
            VkPresentModeKHR modes[16];

            VkSwapchainCreateInfoKHR vkSwapchainCreateInfoKhr = NullStruct;
            vkSwapchainCreateInfoKhr.presentMode = VK_PRESENT_MODE_FIFO_KHR;

            if(vkGetPhysicalDeviceSurfacePresentModesKHR(vkCtx->vkPhysicalDev, vkCtx->vkSurfaceKhr, &presentModeCount, NullPtr) == VK_SUCCESS &&
            vkGetPhysicalDeviceSurfacePresentModesKHR(vkCtx->vkPhysicalDev, vkCtx->vkSurfaceKhr, &presentModeCount, modes) == VK_SUCCESS)
            {
                for(UInt32 i = 0; i < presentModeCount; i++)
                {
                    if(modes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
                    {
                        vkSwapchainCreateInfoKhr.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
                    }

                    DEBUG_LOG(DECIMAL_LOG_FORMAT, GREEN_CONSOLE_COLOR, modes[i]);
                }
            }

            vkSwapchainCreateInfoKhr.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            vkSwapchainCreateInfoKhr.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
            vkSwapchainCreateInfoKhr.surface = vkCtx->vkSurfaceKhr;
            vkSwapchainCreateInfoKhr.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            vkSwapchainCreateInfoKhr.imageArrayLayers = 1;
            vkSwapchainCreateInfoKhr.imageFormat = vkCtx->vkSurfFormat.format;
            vkSwapchainCreateInfoKhr.imageColorSpace = vkCtx->vkSurfFormat.colorSpace;
            vkSwapchainCreateInfoKhr.oldSwapchain = VK_NULL_HANDLE;


            VkSurfaceCapabilitiesKHR vkSurfCapsKhr = NullStruct;
            
            if(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkCtx->vkPhysicalDev, vkCtx->vkSurfaceKhr, &vkSurfCapsKhr) == VK_SUCCESS)
            {
                UInt32 imgCount = vkSurfCapsKhr.minImageCount + 1;
                imgCount = imgCount > vkSurfCapsKhr.maxImageCount ? imgCount - 1 : imgCount;

                DEBUG_INFO("got physical device surface capabilities");
                vkSwapchainCreateInfoKhr.preTransform = vkSurfCapsKhr.currentTransform;
                vkSwapchainCreateInfoKhr.imageExtent = vkSurfCapsKhr.currentExtent;
                vkSwapchainCreateInfoKhr.minImageCount = imgCount;
            }

            if(vkCreateSwapchainKHR(vkCtx->vkDev, &vkSwapchainCreateInfoKhr, NullPtr, &vkCtx->vkSwapchainKhr) != VK_SUCCESS)
            {
                DEBUG_ERROR("fail vulkan create swap chain")
                return 0;
            }

            if( vkGetSwapchainImagesKHR(vkCtx->vkDev, vkCtx->vkSwapchainKhr, &vkCtx->vkSwapchainImgCount, NullPtr) != VK_SUCCESS ||
                vkGetSwapchainImagesKHR(vkCtx->vkDev, vkCtx->vkSwapchainKhr, &vkCtx->vkSwapchainImgCount, vkCtx->vkImgs) != VK_SUCCESS)
            {
                return 0;
            }

            for(int i = 0; i < 2; i++)
            {
                VkImageViewCreateInfo imgViewCreateInfo = NullStruct;
                imgViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                imgViewCreateInfo.image = vkCtx->vkImgs[i];
                imgViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                imgViewCreateInfo.format = vkCtx->vkSurfFormat.format;

                imgViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                imgViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                imgViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                imgViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

                imgViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                imgViewCreateInfo.subresourceRange.baseMipLevel = 0;
                imgViewCreateInfo.subresourceRange.levelCount = 1;
                imgViewCreateInfo.subresourceRange.layerCount = 1;
                imgViewCreateInfo.subresourceRange.baseArrayLayer = 0;

                if(vkCreateImageView(vkCtx->vkDev, &imgViewCreateInfo, NullPtr, &vkCtx->vkImgViews[i]) != VK_SUCCESS)
                {
                    DEBUG_ERROR("failed to create img view");
                }
            }

        }

        VkCommandPoolCreateInfo cmdPoolCreateInfo = {0};
        cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        cmdPoolCreateInfo.queueFamilyIndex = vkCtx->vkGfxIdx;

        if(vkCreateCommandPool(vkCtx->vkDev, &cmdPoolCreateInfo, NullPtr, &vkCtx->vkCmdPool) != VK_SUCCESS)
        {
            return 0;
        }

        {
            VkSemaphoreCreateInfo semaphoreCreateInfo = NullStruct;
            semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            vkCreateSemaphore(vkCtx->vkDev, &semaphoreCreateInfo, NullPtr, &vkCtx->vkSubmitSemaphore);
            vkCreateSemaphore(vkCtx->vkDev, &semaphoreCreateInfo, NullPtr, &vkCtx->vkAcquireSemaphore);
        }
    }

    DEBUG_INFO("EVERYTHING IS OK");
    return 1;
}

Bool Nav_Graphics_Vulkan_Render(VulkanContext* vkCtx)
{
    UInt32 imgIdx = 0;

    if(vkAcquireNextImageKHR(vkCtx->vkDev, vkCtx->vkSwapchainKhr, 0, vkCtx->vkAcquireSemaphore, 0, &imgIdx) == VK_SUCCESS){}
    else
    {return 0;}

    VkCommandBufferAllocateInfo cmdBuffAllocInfo = {0};
    cmdBuffAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmdBuffAllocInfo.commandBufferCount = 1;
    cmdBuffAllocInfo.commandPool = vkCtx->vkCmdPool;

    VkCommandBuffer cmd;
    if(vkAllocateCommandBuffers(vkCtx->vkDev, &cmdBuffAllocInfo, &cmd) != VK_SUCCESS){return 0;}

    VkCommandBufferBeginInfo cmdBuffBeginInfo = NullStruct;
    cmdBuffBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmdBuffBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;


    if(vkBeginCommandBuffer(cmd, &cmdBuffBeginInfo) != VK_SUCCESS){return 0;}
    DEBUG_INFO("render");

    // Render Scope
    {

        VkClearColorValue color = {1, 0, 0, 1};

        VkImageSubresourceRange range = NullStruct;
        range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        range.layerCount = 1;
        range.levelCount = 1;

        VkImageLayout imgLayout = NullStruct;
        imgLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        vkCmdClearColorImage(cmd, vkCtx->vkImgs[imgIdx], VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, &color, 1, &range);
    }

    if(vkEndCommandBuffer(cmd) != VK_SUCCESS){return 0;}

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submitInfo = {0};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pCommandBuffers = &cmd;
    submitInfo.commandBufferCount = 1;
    submitInfo.pWaitSemaphores = &vkCtx->vkAcquireSemaphore;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &vkCtx->vkSubmitSemaphore;
    submitInfo.signalSemaphoreCount = 1;

    submitInfo.pWaitDstStageMask = &waitStage;

    if(vkQueueSubmit(vkCtx->vkQueue, 1, &submitInfo, 0) != VK_SUCCESS){return 0;}


    VkPresentInfoKHR presentInfo;
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext = NullPtr;
    presentInfo.pSwapchains = &vkCtx->vkSwapchainKhr;
    presentInfo.swapchainCount = 1;
    presentInfo.pImageIndices = &imgIdx;
    presentInfo.pWaitSemaphores = &vkCtx->vkSubmitSemaphore;
    presentInfo.waitSemaphoreCount = 1;

    if(vkQueuePresentKHR(vkCtx->vkQueue, &presentInfo) != VK_SUCCESS){return 0;}

    if(vkDeviceWaitIdle(vkCtx->vkDev) != VK_SUCCESS){return 0;}

    vkFreeCommandBuffers(vkCtx->vkDev, vkCtx->vkCmdPool, 1, &cmd);
}