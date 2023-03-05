set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/dependencies/imgui)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/dependencies/glad)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies)

set(GLAD_SOURCES
        ${GLAD_DIR}/src/glad.c
        )

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
        )

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}
        main.cpp
        ${IMGUI_SOURCES}
        ${GLAD_SOURCES}
        ${SRCS}
        )

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
