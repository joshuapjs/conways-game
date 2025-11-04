set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set min CMake version required vor build
cmake_minimum_required(VERSION 3.10)
# Set the project name
project("Conway's Game")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Add necessary Executables
add_executable(main main.cpp World.cpp Cli.cpp)

# Add location of h-files and other ressources
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
