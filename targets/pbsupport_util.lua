target("pbsupport_util")
    set_basename("pbsupport_util")
    add_sysincludedirs("$(projectdir)/External/libb64/include")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("binary")

    add_deps("PBSupport_static", "libb64")
    add_packages("libxml2")

    add_files("$(projectdir)/ProjectBuilder/Tests/pbsupport_util.cpp")
