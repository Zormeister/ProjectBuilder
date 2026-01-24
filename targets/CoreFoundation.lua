task("copy_cf_headers")

    on_run(function ()
        os.mkdir("$(builddir)/include/", "$(builddir)/include/CoreFoundation/")
        os.cp("$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/**.h", "$(builddir)/include/CoreFoundation/")
        -- the copy operation will fetch the SwiftRuntime version instead of what we want.
        os.rm("$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/CoreFoundation.h")
        os.cp("$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/Base.subproj/CoreFoundation.h", "$(builddir)/include/CoreFoundation/CoreFoundation.h")
    end)

task_end()

target("libCoreFoundation")
    set_basename("CoreFoundation")
    add_sysincludedirs(
        "/usr/include/libxml2",
        "$(projectdir)/ThirdParty/CarbonHeaders",
        "$(builddir)/include/"
    )
    add_includedirs(
        "$(builddir)/include/CoreFoundation"
    )

    add_defines(
        "CF_BUILDING_CF=1",
        "DEPLOYMENT_TARGET_LINUX=1",
        "__HAS_DISPATCH__=1",
        "__HAS_BLOCKS__=1",
        "HAVE_STRUCT_TIMESPEC=1",
        "_GNU_SOURCE"
    )

    set_pcheader("$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/Base.subproj/CoreFoundation_Prefix.h")

    set_languages("c99")
    set_kind("static")

    add_cflags(
        "-fblocks",
        "-Wno-incompatible-function-pointer-types"
    )

    add_ldflags("-lxml2", "-ldispatch")

    add_files("$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/**.c")

    remove_files(
        "$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/AppServices.subproj/*.c",
        "$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/RunLoop.subproj/*.c",
        "$(projectdir)/ThirdParty/CoreFoundation/CoreFoundation/Stream.subproj/CFFileDescriptor.c"
    )

    before_prepare(function (target)
        import("core.project.task")

        -- Run the hello task
        task.run("copy_cf_headers")
    end)
