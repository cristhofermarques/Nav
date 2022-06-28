#ifndef NAV_VK_H
#define NAV_VK_H

#include <nav_api.h>
#include <platform/nav_window.h>

struct VulkanContextType;
typedef struct VulkanContextType VulkanContext;

NAV_API VulkanContext* CreateVulkanContext();
NAV_API char DestroyVulkanContext(VulkanContext* vkCtx);

NAV_API char CreateVulkanSurface(VulkanContext* vkCtx, Window* wnd);

#endif