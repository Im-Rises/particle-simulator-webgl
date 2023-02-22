cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(EMSCRIPTEN emcc)
find_program(EMSCRIPTEN_COMPILER emcc)

##set(EMSCRIPTEN_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" CACHE PATH "Emscripten toolchain file")
##set(EMSCRIPTEN_TOOLCHAIN_FILE "${PATH}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" CACHE PATH "Emscripten toolchain file")
#set(EMSCRIPTEN_TOOLCHAIN_FILE ${EMSCRIPTEN}/../cmake/Modules/Platform/Emscripten.cmake CACHE PATH "Emscripten toolchain file")
#set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_TOOLCHAIN_FILE})
#set(CMAKE_C_COMPILER emcc)
#set(CMAKE_CXX_COMPILER em++)

get_filename_component(EMSCRIPTEN_COMPILER_DIR ${EMSCRIPTEN_COMPILER} DIRECTORY)
set(EMSCRIPTEN_TOOLCHAIN_FILE ${EMSCRIPTEN_COMPILER_DIR}/../cmake/Modules/Platform/Emscripten.cmake CACHE PATH "Emscripten toolchain file")
set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_TOOLCHAIN_FILE})
set(CMAKE_C_COMPILER emcc)
set(CMAKE_CXX_COMPILER em++)

project("particle-simulator-webgl" VERSION 0.1.0)

add_subdirectory(${PROJECT_NAME})
