if(!UNIX)
message( FATAL ERROR "This subproject is only for unix systems")
endif()

project(SharedMemory)

add_library(${PROJECT_NAME} STATIC
shared_memory.cpp
)


target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(Sharom::Buffer::SharedMemory ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} 
Sharom::Util
)


target_link_options(${PROJECT_NAME} 
INTERFACE -lrt 
)

