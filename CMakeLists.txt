cmake_minimum_required(VERSION 3.24)

project(ProjectBuilder C CXX)

add_subdirectory(External/date)

find_package(libxml2 REQUIRED)

add_library(PBSupport
    ProjectBuilder/Framework/CXXSupport/Array.cpp
    ProjectBuilder/Framework/CXXSupport/Boolean.cpp
    ProjectBuilder/Framework/CXXSupport/Data.cpp
    ProjectBuilder/Framework/CXXSupport/Date.cpp
    ProjectBuilder/Framework/CXXSupport/Dictionary.cpp
    ProjectBuilder/Framework/CXXSupport/File.cpp
    ProjectBuilder/Framework/CXXSupport/Integer.cpp
    ProjectBuilder/Framework/CXXSupport/String.cpp
    ProjectBuilder/Framework/CXXSupport/Utils.cpp
)

target_compile_definitions(PBSupport PRIVATE TARGET_OS_LINUX=1)

target_link_libraries(PBSupport PUBLIC LibXml2::LibXml2 date::date)

add_library(ProjectBuilder
    ProjectBuilder/Framework/CXX/BuildController.cpp
)

target_link_libraries(ProjectBuilder PUBLIC PBSupport)

target_include_directories(ProjectBuilder PRIVATE ${CMAKE_SOURCE_DIR}/ProjectBuilder/Framework)

add_executable(pbsupport_test
    ProjectBuilder/Tests/pbsupport_util.cpp
)

target_link_libraries(pbsupport_test PUBLIC PBSupport)

target_include_directories(pbsupport_test PRIVATE ${CMAKE_SOURCE_DIR}/ProjectBuilder/Framework)