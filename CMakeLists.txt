cmake_minimum_required(VERSION 3.10)

project(HelloImGuiWeb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_TOOLCHAIN_FILE ~/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)

file(GLOB_RECURSE IMGUI_SOURCES
    ../imgui/*.cpp
    ../imgui/*.h
)

add_executable(HelloImGuiWeb
    main.cpp ${IMGUI_SOURCES}
)

find_package(glfw3 REQUIRED)
target_link_libraries(HelloImGuiWeb glfw)
