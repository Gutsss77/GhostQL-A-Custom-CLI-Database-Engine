cmake_minimum_required(VERSION 3.15)
project(GhostQL VERSION 1.0 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell compiler where to find headers
include_directories(include)

# Add executable and its source files
add_executable(GhostQL main.cpp src/QLParser.cpp src/cli-for-users.cpp
)
