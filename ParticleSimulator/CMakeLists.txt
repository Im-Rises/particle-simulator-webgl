include_directories("${CMAKE_SOURCE_DIR}/dependencies")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/imgui")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/imgui/backends")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glad/include")

file(GLOB_RECURSE SRCS_HEADERS_IMGUI "${CMAKE_SOURCE_DIR}/dependencies/imgui/*.cpp" "${CMAKE_SOURCE_DIR}/dependencies/imgui/*.h")
file(GLOB_RECURSE SRCS_HEADERS_GLAD "${CMAKE_SOURCE_DIR}/dependencies/glad/*.c" "${CMAKE_SOURCE_DIR}/dependencies/glad/*.h")

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

#set(OpenGL_GL_PREFERENCE GLVND)
#find_package(OpenGL 4.3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${HEADERS} ${SRCS_HEADERS_IMGUI} ${SRCS_HEADERS_GLAD})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
