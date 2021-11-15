cmake_minimum_required(VERSION 3.16)
project(drone_visualizer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(lib)
add_subdirectory(external)
add_subdirectory(app)