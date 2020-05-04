cmake_minimum_required(VERSION 3.5)

project(Sharom)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#todo make it prettier
# required with linux code when compiling target as shared library
# required even for static libraries that later get linked into dynamic lib
if(UNIX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()


# add subdirectories with subprojects
add_subdirectory(src/exception)
add_subdirectory(src/utility)
add_subdirectory(src/buffer)
add_subdirectory(src/mutex)

#tests
enable_testing()


add_subdirectory(3rd_party/google-test)

add_executable(unit_test 
test/test.cpp
test/mutex_test.cpp)

add_test(test_all unit_test)

target_link_libraries(unit_test
Sharom::Buffer
Sharom::Mutex
GTest::GTest
GMock::GMock
GTest::Main
GMock::Main
)
