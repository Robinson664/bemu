cmake_minimum_required (VERSION 2.8)
project (BEmu_cpp)

find_package(Boost REQUIRED COMPONENTS system date_time thread regex)
include_directories(${Boost_INCLUDE_DIRS})
add_definitions("-DBOOST_ALL_NO_LIB")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()

add_subdirectory(BEmu_cpp)
add_subdirectory(Examples_cpp)
