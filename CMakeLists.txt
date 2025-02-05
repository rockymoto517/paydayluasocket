cmake_minimum_required(VERSION 3.15)

project(lua_socket VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE release)

# For convenience's sake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform setup
add_compile_definitions(WIN32)
add_compile_definitions(_WIN32)

# Create target
file(GLOB_RECURSE sources src/*.cpp)
add_library(luasocket SHARED ${sources})
target_include_directories(luasocket PUBLIC include)
set_property(TARGET luasocket PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Link to winsock
target_link_libraries(luasocket PRIVATE wsock32 ws2_32)

# Link to SuperBLT
target_link_libraries(luasocket PRIVATE ${PROJECT_SOURCE_DIR}/lib/sblt_plugin.lib)

