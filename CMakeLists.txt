cmake_minimum_required(VERSION 3.0)

project(particle-simulator-webgl)

include_directories(dependencies/glad/include)

set(CMAKE_CXX_STANDARD 11)

set(IMGUI_DIR dependencies/imgui)
set(GLAD_DIR dependencies/glad)

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

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
endif()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s FULL_ES3=1 -s WASM=0 -s ALLOW_MEMORY_GROWTH=1")
endif()
