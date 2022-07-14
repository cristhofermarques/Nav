add_rules("mode.debug", "mode.release")

-- NAV
target("nav")

    set_kind("shared")


    -- C Version
    set_languages("c11")


    -- Vulkan
    add_includedirs("C:/VulkanSDK/1.3.216.0/Include")
    add_linkdirs("C:/VulkanSDK/1.3.216.0/Lib")
    add_links("vulkan-1")


    -- Platform Build Trait
    if is_plat("mingw") then

        set_prefixname("")

    end


    -- Nav Api Export
   add_cflags("-DNAV_API_EXPORT")


    -- Nav Header
    add_includedirs("Nav/Header")


    -- Nav Debug Build Trait
    if is_mode("debug") then

        add_cflags("-DDEBUG")

    end


    -- Nav No Platform Depedent Source Files
    add_files("Nav/Source/Extension/*.c");


    -- Nav Vulkan Source Files
    add_files("Nav/Source/Graphics/Vulkan/*.c");


    -- Nav OS Source Files Trait
    if is_os("windows") then

        add_files("Nav/Source/Platform/Win32/*.c")
        add_links("user32")

    end


-- LAUNCHER
target("launcher")

    set_kind("binary")

    set_languages("c11")

    -- Vulkan
    add_includedirs("C:/VulkanSDK/1.3.216.0/Include")
    add_linkdirs("C:/VulkanSDK/1.3.216.0/Lib")
    add_links("vulkan-1")


    -- Launcher

    -- Nav Header
    add_includedirs("Nav/Header")
    add_includedirs("launcher/")
    
    -- Nav Dependencie
    add_deps("nav")

    -- Launcher Debug Build Trait

    if is_mode("debug") then

        add_cflags("-DDEBUG")

    end

    -- Launcher Core Files
    add_files("launcher/src/*.c")