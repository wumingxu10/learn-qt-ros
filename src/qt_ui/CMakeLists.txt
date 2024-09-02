cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
project(qt_ui)

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


find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

#************************
# 添加源文件
#************************
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.h)
# file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)
set(QT_SOURCES mainwindow.cpp  rosNode.cpp)

#三个用于处理Qt特定资源和代码生成的命令
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS}) #从 .ui 文件自动生成用户界面类的头文件和源文件
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})#将 .qrc 资源文件转换成可编译的C++源文件
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #.h 文件（包含Qt对象的头文件）自动生成moc（元对象编译器）文件，这些文件是Qt信号和槽机制所必需的

#ament_package()

add_library(${PROJECT_NAME} SHARED  ${QT_FORMS_HPP}
                                    ${QT_RESOURCES_CPP}       
                                    ${QT_MOC_HPP} 
                                    ${QT_SOURCES})
                                    

ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)


add_executable(${PROJECT_NAME}_test main.cpp)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})