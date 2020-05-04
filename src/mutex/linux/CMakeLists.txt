if(!UNIX)
message( FATAL ERROR "This subproject is only for unix systems")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS ON)
project(MutexImpl)


add_library(${PROJECT_NAME} STATIC
mutex_impl.cpp
)


target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_link_options()
target_link_options(${PROJECT_NAME} PRIVATE
-lrt
-pthread)

target_compile_definitions(${PROJECT_NAME}
PRIVATE _POSIX_C_SOURCE=200809L
PRIVATE _XOPEN_SOURCE=700 #Todo check if still needed
)
#_POSIX_C_SOURCE=200809L should be equivalent to _XOPEN_SOURCE=700
#https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02



target_link_libraries(${PROJECT_NAME} PUBLIC
Sharom::Exceptions
)

add_library(Sharom::Mutex::MutexImpl ALIAS ${PROJECT_NAME})

