cmake_minimum_required(VERSION 4.0)
project(last_mouse_maze)

set(CMAKE_CXX_STANDARD 20)

add_executable(last_mouse_maze main.cpp
        MazeRepresentation.cpp
        DFS_implementation.cpp)
