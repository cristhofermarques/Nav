#ifndef NAV_VULKAN_CONTEXT_STRUCT_H
#define NAV_VULKAN_CONTEXT_STRUCT_H

#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <vulkan/vulkan.h>

struct VulkanContextType
{
    UInt32 vkGfxIdx;
    UInt32 vkSwapchainImgCount;
    VkImage vkImgs[3];
    VkInstance vkInstance;
    VkSurfaceKHR vkSurfaceKhr;
    VkPhysicalDevice vkPhysicalDev;
    VkDevice vkDev;
    VkSwapchainKHR vkSwapchainKhr;
    VkDebugUtilsMessengerEXT vkDebugMessenger;
    VkSurfaceFormatKHR vkSurfFormat;
    VkQueue vkQueue;
    VkCommandPool vkCmdPool;
    VkSemaphore vkSubmitSemaphore;
    VkSemaphore vkAcquireSemaphore;

    VkImageView vkImgViews[3];
};

#endif // NAV_VULKAN_CONTEXT_STRUCT_H