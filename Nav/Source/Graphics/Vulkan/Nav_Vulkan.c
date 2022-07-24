#include <Nav_Debug.h>
#include <Memory/Nav_Allocation.h>
#include <Graphics/Vulkan/Nav_Vulkan.h>
#include <Graphics/Vulkan/Nav_Vulkan_Context_Struct.h>
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

static VKAPI_ATTR VkBool32 VKAPI_CALL VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT msgServerity, VkDebugUtilsMessageTypeFlagsEXT msgFlags, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData)
{
    DEBUG_ERROR(callbackData->pMessage);
}


VulkanContext* CreateVulkanContext()
{
    VkApplicationInfo vkAppInfo = {0};
    vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vkAppInfo.apiVersion = VK_API_VERSION_1_0;
    vkAppInfo.pApplicationName = "NavApp";
    vkAppInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    vkAppInfo.pEngineName = "Nav";
    vkAppInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);

    char* enabledExts[] = 
    {
        VK_KHR_SURFACE_EXTENSION_NAME,
        "VK_KHR_win32_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    };

    char* enabledLayers[] = 
    {
        "VK_LAYER_KHRONOS_validation"
    };

    {
        UInt32 extPropCount = 0;
        if(vkEnumerateInstanceExtensionProperties(NullPtr, &extPropCount, NullPtr) == VK_SUCCESS)
        {   
            VkExtensionProperties* extProps = NAV_MEMORY_ALLOCATE(sizeof(VkExtensionProperties) * extPropCount);

            if(extProps != NullPtr)
            {
                if(vkEnumerateInstanceExtensionProperties(NullPtr, &extPropCount, extProps) == VK_SUCCESS)
                {
                    for(UInt32 extPropIdx =  0; extPropIdx < extPropCount; extPropIdx++)
                    {
                        VkExtensionProperties extProp = extProps[extPropIdx];

                        DEBUG_LOG("Name : " STRING_LOG_FORMAT " Version : " DECIMAL_LOG_FORMAT, GREEN_CONSOLE_COLOR, extProp.extensionName, extProp.specVersion);
                    }
                }

                NAV_MEMORY_DEALLOCATE(extProps);
            }
        }
    }

    VkInstanceCreateInfo vkInstanceCreateInfo = {0};
    vkInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    vkInstanceCreateInfo.pApplicationInfo = &vkAppInfo;
    vkInstanceCreateInfo.ppEnabledExtensionNames = enabledExts;
    vkInstanceCreateInfo.enabledExtensionCount = 3;
    vkInstanceCreateInfo.ppEnabledLayerNames = enabledLayers;
    vkInstanceCreateInfo.enabledLayerCount = 1;

    VkInstance vkInstance = {0};

    if(vkCreateInstance(&vkInstanceCreateInfo, 0, &vkInstance) == VK_SUCCESS)
    {
        VulkanContext* vkCtx = malloc(sizeof(VulkanContext));
        vkCtx->vkInstance = vkInstance;

        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkCtx->vkInstance, "vkCreateDebugUtilsMessengerEXT");


        if(vkCreateDebugUtilsMessengerEXT != NullPtr)
        {
            DEBUG_INFO("vkCreateDebugUtilsMessengerEXT loaded")
            
            VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMsgCreateInfoExt = {0};
            vkDebugUtilsMsgCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            vkDebugUtilsMsgCreateInfoExt.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            vkDebugUtilsMsgCreateInfoExt.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
            vkDebugUtilsMsgCreateInfoExt.pfnUserCallback = VkDebugCallback;

            vkCreateDebugUtilsMessengerEXT(vkCtx->vkInstance, &vkDebugUtilsMsgCreateInfoExt, 0, &vkCtx->vkDebugMessenger);
        }
        return vkCtx;
    }

    return NullPtr;
}

char DestroyVulkanContext(VulkanContext* vkCtx)
{
    if(vkCtx != NULL)
    {

        if(&vkCtx->vkSwapchainKhr != NullPtr)
        {
            vkDestroySwapchainKHR(vkCtx->vkDev, vkCtx->vkSwapchainKhr, NullPtr);
        }

        vkDestroyRenderPass(vkCtx->vkDev, vkCtx->vkRenderPass, NullPtr);

        for(int i = 0; i < vkCtx->vkSwapchainImgCount; i++)
        {
            vkDestroyFramebuffer(vkCtx->vkDev, vkCtx->vkFramebuffers[i], NullPtr);
            vkDestroyImageView(vkCtx->vkDev, vkCtx->vkImgViews[i], NullPtr);
        }
        vkDestroySurfaceKHR(vkCtx->vkInstance, vkCtx->vkSurfaceKhr, NullPtr);

        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkCtx->vkInstance, "vkCreateDebugUtilsMessengerEXT");
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkCtx->vkInstance, "vkDestroyDebugUtilsMessengerEXT");

        if(vkDestroyDebugUtilsMessengerEXT != NullPtr)
        {
            vkDestroyDebugUtilsMessengerEXT(vkCtx->vkInstance, vkCtx->vkDebugMessenger, NullPtr);
        }


        vkDestroyDevice(vkCtx->vkDev, NullPtr);
        vkDestroyInstance(vkCtx->vkInstance, 0);

        free(vkCtx);
        return 1;
    }

    return 0;
}

unsigned int GetGraphicsIndexOfVulkanContext(VulkanContext* vkCtx)
{
    if(vkCtx == NULL){return UINT32_MAX;}

    return vkCtx->vkGfxIdx;
}