cmake_minimum_required(VERSION 3.10)
project(SimGarden VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Plant.cpp
    src/Garden.cpp
)

# Create executable
add_executable(simgarden ${SOURCES})

# Installation
install(TARGETS simgarden DESTINATION bin)
