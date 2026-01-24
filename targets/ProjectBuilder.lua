target("libProjectBuilder")
    set_basename("ProjectBuilder")
    add_sysincludedirs(
        "$(projectdir)/ThirdParty/CarbonHeaders",
        "$(builddir)/include/",
        "$(projectdir)/include"
    )

    add_deps("libCoreFoundation")

    set_languages("c11")
    set_kind("shared")

    add_cflags("-fblocks")

    add_ldflags("-ldispatch")

    add_files("$(projectdir)/src/ProjectBuilder/**.c")
