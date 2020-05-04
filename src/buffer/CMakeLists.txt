cmake_minimum_required(VERSION 3.13)

project(Buffer)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

if(UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(WIN32)
SET(OS_SPECIFIC win)
elseif(UNIX)
SET(OS_SPECIFIC linux)
endif()

add_library(${PROJECT_NAME} STATIC
src/buffer.cpp
src/settings.cpp
src/buffer_impl.hpp
src/buffer_impl.cpp
src/c_api.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_library(Sharom::Buffer ALIAS ${PROJECT_NAME})

add_subdirectory(src/${OS_SPECIFIC})

target_link_libraries(${PROJECT_NAME} PUBLIC
Sharom::Buffer::SharedMemory
Sharom::Exceptions
)


#TODO export to separate file?
project(Buffer_C_API)
add_library(${PROJECT_NAME} SHARED
src/c_api.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
Sharom::Buffer
)

if(UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
