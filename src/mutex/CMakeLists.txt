cmake_minimum_required(VERSION 3.13)

project(Mutex)

if(WIN32)
SET(OS_SPECIFIC win)
elseif(UNIX)
SET(OS_SPECIFIC linux)
endif()

add_library(${PROJECT_NAME} STATIC
mutex.cpp
)
add_library(Sharom::Mutex ALIAS ${PROJECT_NAME})

add_subdirectory(${OS_SPECIFIC})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
Sharom::Mutex::MutexImpl
)

