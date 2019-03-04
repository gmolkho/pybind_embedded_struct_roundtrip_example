cmake_minimum_required (VERSION 3.13)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project (PyBindBasicexample)

set(CMAKE_CXX_STANDARD 14)

message("Processing CMakeLists.txt")

add_subdirectory (ifc_lib)
add_subdirectory (test_driver)
add_subdirectory (src_python build)




