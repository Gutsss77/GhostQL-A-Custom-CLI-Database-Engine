cmake_minimum_required(VERSION 3.15)
project(GhostQL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include libs)

# Define source files
add_executable(GhostQL
    main.cpp
    src/QLParser.cpp
    src/processCommand.cpp
    src/database.cpp
    src/helper.cpp
)

#for using the root directory
target_compile_definitions(GhostQL PRIVATE SOURCE_DIR="${CMAKE_SOURCE_DIR}")