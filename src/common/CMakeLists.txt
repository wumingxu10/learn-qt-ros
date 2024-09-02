cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
project(common)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

set(CMAKE_CXX_FLAGS "-w")# 忽略警告信息
set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb ${CMAKE_CXX_FLAGS}")# 设置DEBUG模式的编译选项
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -ggdb ${CMAKE_CXX_FLAGS}")# 设置RELEASE模式的编译选项

message(STATUS "PROJECT_NAME = ${PROJECT_NAME}")


set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED common.cpp myLog.cpp)
target_link_libraries(${PROJECT_NAME} glog)


add_executable(${PROJECT_NAME}_test main_common_test.cpp)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME} )