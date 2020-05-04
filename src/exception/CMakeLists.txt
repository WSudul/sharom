cmake_minimum_required(VERSION 3.5)

project(Exceptions)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC
 sharom_exception.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_library(Sharom::Exceptions ALIAS ${PROJECT_NAME})

