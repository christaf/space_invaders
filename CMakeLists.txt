cmake_minimum_required(VERSION 3.21)
project(engine_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Engine.cpp
        src/Engine.h
        src/Particle.cpp
        src/Particle.h
        src/shapes.h
        src/Bullet.cpp
        src/Bullet.h
        src/Spaceship.cpp
        src/Spaceship.h)
target_link_libraries(engine_project -lopengl32 -lglfw3 -lgdi32 -lfreeglut -Dglm_DIR=C:/msys64/mingw64/include/glm/glm/ -lglu32)
