#ifndef NAV_VK_H
#define NAV_VK_H

#include <Nav_Api.h>
#include <Platform/Nav_Window.h>
#include <vulkan/vulkan.h>

#define VK_CHECK_FAIL_TO_RETURN_FUNC(vkResult, onFailCode) \
    if(vkResult != VK_SUCCESS) \
    { \
        onFailCode; \
        return; \
    }

#define VK_CHECK_FAIL(vkResult, onFailCode) \
    if(vkResult != VK_SUCCESS) \
    { \
        onFailCode; \
    }


struct VulkanContextType;
typedef struct VulkanContextType VulkanContext;

NAV_API VulkanContext* CreateVulkanContext();
NAV_API char DestroyVulkanContext(VulkanContext* vkCtx);

NAV_API char CreateVulkanSurface(VulkanContext* vkCtx, Nav_Window* wnd);

NAV_API unsigned int GetGraphicsIndexOfVulkanContext(VulkanContext* vkCtx);

NAV_API Bool Nav_Graphics_Vulkan_Render(VulkanContext* vkCtx);

#endif