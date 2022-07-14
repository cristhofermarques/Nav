#ifndef NAV_VULKAN_CONTEXT_STRUCT_H
#define NAV_VULKAN_CONTEXT_STRUCT_H

#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <vulkan/vulkan.h>

struct VulkanContextType
{
    unsigned int vkGfxIdx;
    VkInstance vkInstance;
    VkSurfaceKHR vkSurfaceKhr;
    VkPhysicalDevice vkPhysicalDev;
    VkDevice vkDev;
    VkSwapchainKHR vkSwapchainKhr;
};

#endif // NAV_VULKAN_CONTEXT_STRUCT_H