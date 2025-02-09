cmake_minimum_required(VERSION 3.14)
project(macrodb)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing and CTest
include(CTest)

enable_testing()

# Create the main library
set(LIB_NAME "macrodb")


add_library(${LIB_NAME} STATIC
    src/macrodb.c
    src/macrodbsafety.c
    src/macrodbmapper.c
)


target_include_directories(${LIB_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/table
        ${CMAKE_CURRENT_SOURCE_DIR}/include/platform
)

# Only build tests if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(tests)
endif()