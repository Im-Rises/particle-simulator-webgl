cmake_minimum_required(VERSION 3.8)

project(particle-simulator-webgl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Release build type by default to get optimization flags
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Build type not specified: Use Release by default")
endif ()

if (EMSCRIPTEN)
    #    set(CMAKE_EXECUTABLE_SUFFIX ".html")gi
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")
endif ()

add_subdirectory(ParticleSimulator)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/web)
    #    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "index")
endif ()
