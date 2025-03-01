cmake_minimum_required(VERSION 3.24)

project(ProjectBuilder C CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(CoreFoundation REQUIRED CoreFoundation)

find_package(libxml2)

add_library(ProjectBuilder
    ProjectBuilder/Framework/PBBuildController.c
    ProjectBuilder/Framework/PBDiskImage.c
    ProjectBuilder/Framework/PBConstants.c
)

target_link_libraries(ProjectBuilder ${CoreFoundation_LIBRARIES} LibXml2::LibXml2)
target_include_directories(ProjectBuilder PUBLIC ${CoreFoundation_INCLUDE_DIRS})
target_compile_options(ProjectBuilder PUBLIC ${CoreFoundation_CFLAGS_OTHER})