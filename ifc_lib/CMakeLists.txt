cmake_minimum_required(VERSION 3.13)
project(ifc_lib)

set(CMAKE_CXX_STANDARD 14)
set(PYBIND11_CPP_STANDARD -std=c++14)
message("Processing Lib CMakeLists.txt")
# Pybind11
include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG        v2.2.4
)
FetchContent_GetProperties(pybind11)
if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
endif()

find_path(PYBIND11_INCLUDE_DIR pybind11.h
        HINTS ${PYBIND11_ROOT}
        PATH_SUFFIXES include)
set(pybind11 PYBIND11_INCLUDE_DIR)
message("DEBUG: found PYBIND11_INCLUDE_DIR in  ${PYBIND11_INCLUDE_DIR}")
include_directories(${PYBIND11_INCLUDE_DIR})

# Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
message("DEBUG: found PYTHON_INCLUDE_DIRS in  ${PYTHON_INCLUDE_DIRS}")

# General / External
find_path(EXT_HEADER_FILES_DIR ex_struct.h
        HINTS ../test_driver
        PATH_SUFFIXES include)
#set (EXT_HEADER_FILES_DIR ../test_driver)
message("DEBUG: found EXT_HEADER_FILES_DIR in  ${EXT_HEADER_FILES_DIR}")
include_directories(../test_driver)
set (EXT_HEADER_FILES ${EXT_HEADER_FILES_DIR}/ex_struct.h)

# Library
set(HEADER_FILES 
        library.h
        my_class.h
        my_pybind.h
        my_utils.h)
set(SOURCE_FILES
        library.cpp
        my_class.cpp
        my_pybind.cpp
        )
add_library(ifc_lib SHARED ${SOURCE_FILES} ${EXT_HEADER_FILES} ${HEADER_FILES})
target_link_libraries(ifc_lib ${PYTHON_LIBRARIES} pybind11::embed)
