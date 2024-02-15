#include <cstdlib>
#include "GL/glew.h"
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include "Particle.h"
#include "Bullet.h"
#include "Engine.cpp"

#define MAX_PART 1000
#define ACTIVATE_TIME 0.1


Engine *Engine::instance = nullptr;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Particle Fountain");

    Engine::instance = new Engine();
    Engine::run();

    return 0;
}