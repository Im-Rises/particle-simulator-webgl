set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/web)

include_directories("${CMAKE_SOURCE_DIR}/dependencies")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glad/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw/include")

file(GLOB_RECURSE SRCS_HEADERS_IMGUI "${CMAKE_SOURCE_DIR}/dependencies/imgui/*.cpp" "${CMAKE_SOURCE_DIR}/dependencies/imgui/*.h")
file(GLOB_RECURSE SRCS_HEADERS_GLAD "${CMAKE_SOURCE_DIR}/dependencies/glad/*.c" "${CMAKE_SOURCE_DIR}/dependencies/glad/*.h")
file(GLOB_RECURSE SRCS_HEADERS_GLM "${CMAKE_SOURCE_DIR}/dependencies/glm/*.c" "${CMAKE_SOURCE_DIR}/dependencies/glm/*.h")

file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.h")

add_subdirectory("${CMAKE_SOURCE_DIR}/dependencies/glfw" build)
find_package(OpenGL 4.6 REQUIRED)
#find_package(Threads REQUIRED)

add_compile_options("-s WASM=1")

add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS} ${SRCS_HEADERS_IMGUI} ${SRCS_HEADERS_GLAD})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} "-s USE_GLFW=3" "-s MIN_WEBGL_VERSION=2" "-s MAX_WEBGL_VERSION=2")
#target_link_libraries(${PROJECT_NAME} Threads::Threads)

# Copy the html file to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/web/index.html
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.html)
