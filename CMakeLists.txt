cmake_minimum_required(VERSION 3.10)

project(server-cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add all source files and headers in src and src/utils
file(GLOB_RECURSE SOURCES src/*.cpp src/utils/*.cpp main.cpp)
file(GLOB_RECURSE HEADERS src/*.h src/utils/*.h)

# Create the executable
add_executable(server-cpp ${SOURCES} ${HEADERS})
