target("PBSupport_static")
    set_basename("PBSupport")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("static")

    add_packages("libxml2", "vcpkg::b64")

    add_files("$(projectdir)/ProjectBuilder/Framework/CXXSupport/*.cpp")

target("PBSupport_shared")
    set_basename("PBSupport")
    add_includedirs("$(projectdir)/ProjectBuilder/Framework")
    set_languages("c++17")
    set_kind("shared")

    add_packages("libxml2", "vcpkg::b64")

    add_files("$(projectdir)/ProjectBuilder/Framework/CXXSupport/*.cpp")