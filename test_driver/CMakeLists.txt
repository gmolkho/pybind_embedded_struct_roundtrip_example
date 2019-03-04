cmake_minimum_required(VERSION 3.13)
project(test_driver)

set(CMAKE_CXX_STANDARD 14)
message("Processing test CMakeLists.txt")
# General / External
set(MY_ROOT_FOLDER ~/trees/npu-stack)

# Library
find_path(EXT_HEADER_FILES_DIR ex_struct.h
       HINTS ../test_driver
        PATH_SUFFIXES include)
#set (EXT_HEADER_FILES ${EXT_HEADER_FILES_DIR}/ex_struct.h)
set(LIB_DIR ../ifc_lib)
include_directories(${LIB_DIR} ${EXT_HEADER_FILES_DIR})
set(LIB_HEADER_FILES ${LIB_DIR}/library.h)
# Test
set(HEADER_FILES ex_struct.h) # ${HEADER_FILES}
add_executable(test_driver main.cpp ${HEADER_FILES}   )
# Link the executable to the library. Since the  library has
# public include directories we will use those link directories when building
target_link_libraries(test_driver LINK_PRIVATE ifc_lib)
