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

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
