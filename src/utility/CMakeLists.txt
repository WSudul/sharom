cmake_minimum_required(VERSION 3.5)

project(Util)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Add a library with the above sources
add_library(${PROJECT_NAME} STATIC
 utility.cpp
 system_info.cpp)

 target_include_directories(${PROJECT_NAME}
 PUBLIC 
 ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(Sharom::Util ALIAS ${PROJECT_NAME})

target_link_libraries( ${PROJECT_NAME}
    PUBLIC 
    Sharom::Exceptions
)