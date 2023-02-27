cmake_minimum_required(VERSION 3.0)

project(particle-simulator-webgl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Set Release build type by default to get optimization flags
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "Build type not specified: Use Release by default")
endif ()

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/dependencies/imgui)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/dependencies/glad)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies)

add_executable(${PROJECT_NAME}
        main.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${GLAD_DIR}/src/glad.c
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE ${IMGUI_DIR}
        PRIVATE ${IMGUI_DIR}/backends)

#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
#find_package(glfw3 REQUIRED)

#if(UNIX)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
#endif()

#if(APPLE)
#    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
#endif()

#if (EMSCRIPTEN)
#    set(CMAKE_EXECUTABLE_SUFFIX ".html")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")
#endif ()
