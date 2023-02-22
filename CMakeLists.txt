cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)

project("particle-simulator-webgl" VERSION 0.1.0)

add_subdirectory(${PROJECT_NAME})
