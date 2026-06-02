cmake_minimum_required(VERSION 3.20)
project(lifeful C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

set(GLFW_DIR "C:/GLFW")

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES 
    IMPORTED_LOCATION "${GLFW_DIR}/lib-mingw-w64/libglfw3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_DIR}/include"
)

file(GLOB_RECURSE SOURCES "src/*.c")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(lifeful ${SOURCES})

set_target_properties(lifeful PROPERTIES WIN32_EXECUTABLE TRUE)

target_include_directories(lifeful PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(lifeful PRIVATE
    Vulkan::Vulkan
    glfw
)

target_compile_options(lifeful PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)
