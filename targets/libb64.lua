target("libb64")
    set_basename("b64")
    add_sysincludedirs("$(projectdir)/External/libb64/include")
    set_languages("c11")
    set_kind("static")

    add_files("$(projectdir)/External/libb64/src/*.c")
