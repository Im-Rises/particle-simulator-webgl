cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(EMSCRIPTEN emcc)
find_program(EMSCRIPTEN_COMPILER emcc)

if (NOT EMSCRIPTEN)
    message(FATAL_ERROR "emcc not found")
endif()

if (NOT EMSCRIPTEN_COMPILER)
    message(FATAL_ERROR "emcc not found")
endif()

get_filename_component(EMSCRIPTEN_COMPILER_DIR ${EMSCRIPTEN_COMPILER} DIRECTORY)

message(STATUS "EMSCRIPTEN_COMPILER_DIR: ${EMSCRIPTEN_COMPILER_DIR}")
set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)

project("particle-simulator-webgl" VERSION 0.1.0)

add_subdirectory(${PROJECT_NAME})
