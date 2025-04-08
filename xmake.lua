includes("targets/*.lua")

add_requires("libxml2", "vcpkg::b64")

add_rules("mode.release", "mode.debug")

if is_plat(linux) then
    add_defines("TARGET_OS_LINUX=1")
elseif is_plat(macos) then 
    add_defines("TARGET_OS_MAC=1")
end