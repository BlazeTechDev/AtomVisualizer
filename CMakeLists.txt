cmake_minimum_required(VERSION 3.26)
project(AtomVisualizer C)

find_package(OpenGL REQUIRED)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/ext/cglm)

set(CMAKE_C_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/ext/glad/include)

add_executable(AtomVisualizer main.c
        core/window.c
        core/window.h
        core/core.c
        core/core.h
        core/input.c
        core/input.h
        ${PROJECT_SOURCE_DIR}/ext/glad/src/glad.c
        graphics/shader.c
        graphics/shader.h
        graphics/buffer.c
        graphics/buffer.h
        core/io.c
        core/io.h
        graphics/utils.c
        graphics/utils.h)

file(REMOVE ${PROJECT_SOURCE_DIR}/local/)
file(COPY ${PROJECT_SOURCE_DIR}/local/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/local/)

target_link_libraries(AtomVisualizer cglm)
target_link_libraries(AtomVisualizer glfw)
target_link_libraries(AtomVisualizer OpenGL::GL)