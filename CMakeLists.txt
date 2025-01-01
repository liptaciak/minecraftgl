cmake_minimum_required(VERSION 3.10)

project(MinecraftGL)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)
set(INCLUDE_DIR include)

file(GLOB SRC_FILES "${SRC_DIR}/*.c")

include_directories(${INCLUDE_DIR})

add_executable(program ${SRC_FILES})

target_link_libraries(program glfw dl)
