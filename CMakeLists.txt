cmake_minimum_required(VERSION 3.10)

project(server-cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

## Use file globbing to find all source files in the src directory
file(GLOB SOURCES "src/*.cpp" "src/utils/*.cpp" "src/utils/*.h")

# Add your source files here
add_executable(server-cpp ${SOURCES})