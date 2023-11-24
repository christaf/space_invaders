cmake_minimum_required(VERSION 3.21)
project(engine_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Engine.cpp
        src/Engine.h)
target_link_libraries(engine_project -lopengl32 -lglfw3 -lgdi32 -lfreeglut)