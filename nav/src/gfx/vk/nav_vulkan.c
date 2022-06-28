#include <nav_debug.h>
#include <gfx/vk/nav_vk.h>
#include <gfx/vk/nav_vk_context_struct.h>
#include <vulkan/vulkan.h>
#include <stdlib.h>

#define VK_SUCCESS_CHECK(vkResult, successCode, failCode) \
    if(vkResult == VK_SUCCESS) \
    { \
        successCode \
    } \
    else \
    { \
        failCode \
    } \


VulkanContext* CreateVulkanContext()
{
    VkApplicationInfo vkAppInfo = {0};
    vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkAppInfo.pEngineName = "nav";
    vkAppInfo.pApplicationName = "nav_app";

    char* enabledExts[] = 
    {
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_KHR_win32_surface"
    };

    VkInstanceCreateInfo vkInstanceCreateInfo = {0};
    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.pApplicationInfo = &vkAppInfo;
    vkInstanceCreateInfo.ppEnabledExtensionNames = enabledExts;
    vkInstanceCreateInfo.enabledExtensionCount = 2;

    VkInstance vkInstance = {0};
    VK_SUCCESS_CHECK(vkCreateInstance(&vkInstanceCreateInfo, 0, &vkInstance),
    VulkanContext* vkCtx = malloc(sizeof(VulkanContext));
    vkCtx->vkInstance = vkInstance;
    return vkCtx;,
    return NULL;)
}

char DestroyVulkanContext(VulkanContext* vkCtx)
{
    if(vkCtx != NULL)
    {
        vkDestroyInstance(vkCtx->vkInstance, 0);

        free(vkCtx);
        return 1;
    }

    return 0;
}