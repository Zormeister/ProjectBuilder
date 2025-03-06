cmake_minimum_required(VERSION 3.24)

project(ProjectBuilder C CXX)

find_package(libxml2 REQUIRED)

add_library(PBSupport
    ProjectBuilder/Framework/CXXSupport/File.cpp
)

target_link_libraries(PBSupport PUBLIC LibXml2::LibXml2)


add_executable(pbsupport_test
    ProjectBuilder/Tests/pbsupport_util.cpp
)

target_link_libraries(pbsupport_test PUBLIC PBSupport)