target("pbsupport_util")
    set_basename("pbsupport_util")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("binary")

    add_deps("PBSupport_static")
    add_packages("libxml2", "vcpkg::b64")

    add_files("$(projectdir)/ProjectBuilder/Tests/pbsupport_util.cpp")