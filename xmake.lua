add_rules("mode.debug", "mode.release")

target("nav")
    set_kind("shared")

    -- Vulkan
    add_includedirs("C:/VulkanSDK/1.3.216.0/Include")
    add_linkdirs("C:/VulkanSDK/1.3.216.0/Lib")
    add_links("vulkan-1")

    -- D3D11
    add_links("dxgi")
    add_links("d3d11")

    -- Nav

    -- Nav Api Export
   add_cflags("-DNAV_API_EXPORT")


    -- Nav Headers
    add_includedirs("nav/hdr")

    
    -- Nav Debug Build Trait
    if is_mode("debug") then

        add_cflags("-DDEBUG")

    end

    -- Nav Vulkan Files
    add_files("nav/src/gfx/vk/*.c")

    -- Nav OS Trait
    if is_os("windows") then

        add_files("nav/src/platform/win32/*.c")
        add_links("user32")

    end

target("launcher")
    set_kind("binary")


    -- Launcher

    -- Nav Headers
    add_includedirs("nav/hdr")
    
    -- Nav Dependencie
    add_deps("nav")
    
        add_links("dxgi")
    add_links("d3d11")

    -- Launcher Debug Build Trait

    if is_mode("debug") then

        add_cflags("-DDEBUG")

    end

    -- Launcher Core Files
    add_files("launcher/src/*.c")
