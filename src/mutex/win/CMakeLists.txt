
if(!WIN32)
message( FATAL ERROR "This subproject is only for windows systems")
endif()


project(MutexImpl)

add_library(${PROJECT_NAME} STATIC
mutex_impl.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
Sharom::Exceptions
)

add_library(Sharom::Mutex::MutexImpl ALIAS ${PROJECT_NAME})
