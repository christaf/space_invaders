cmake_minimum_required(VERSION 3.21)
project(engine_project)

find_package(glfw3 REQUIRED)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(glad STATIC src/glad.c)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp src/*.c src/*.h tests/*.cpp tests/*.hpp)

add_executable(${PROJECT_NAME}  main.cpp src/glad.c)
target_link_libraries(engine_project -lopengl32 -lglfw3 -lgdi32)

#https://www.youtube.com/watch?v=1s8C9dXRXmM&t=94s <-- TODO setup here