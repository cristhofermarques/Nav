#ifndef NAV_VK_CONTEXT_STRUCT_H
#define NAV_VK_CONTEXT_STRUCT_H

#include <gfx/vk/nav_vk.h>
#include <vulkan/vulkan.h>

struct VulkanContextType
{
    unsigned int vkGfxIdx;
    VkInstance vkInstance;
    VkSurfaceKHR vkSurfaceKhr;
};

#endif