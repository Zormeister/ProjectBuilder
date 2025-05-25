target("PBSupport_static")
    set_basename("PBSupport")
    add_sysincludedirs("$(projectdir)/External/libb64/include")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("static")

    add_deps("libb64")
    add_packages("libxml2")

    add_files("$(projectdir)/ProjectBuilder/Framework/CXXSupport/*.cpp")

target("PBSupport_shared")
    set_basename("PBSupport")
    add_sysincludedirs("$(projectdir)/External/libb64/include")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("shared")

    add_deps("libb64")
    add_packages("libxml2")

    add_files("$(projectdir)/ProjectBuilder/Framework/CXXSupport/*.cpp")
