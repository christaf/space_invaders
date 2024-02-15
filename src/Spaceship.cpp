//
// Created by mateu on 15.02.2024.
//
#include "Spaceship.h"
#include "GL/freeglut.h "
#include <cstdlib>
#include <cmath>


#define USE_MATH_DEFINES
#define F_RAND() ((float)rand()/RAND_MAX)

Spaceship::~Spaceship() = default;

Spaceship::Spaceship() {
    activate();

    r = 1.0f;
    g = F_RAND();
    b = F_RAND();

    active = false;
    size = F_RAND() * 5.0f + 0.5f;

}

Spaceship::Spaceship(float start_x, float start_y, float start_z) {
    posX = start_x;
    posY = start_y;
    posZ = start_z;

    active = false;
    activate();

    r = 1.0f;
    g = F_RAND();
    b = F_RAND();

    size = F_RAND() * 5.0f + 0.5f;

}

void Spaceship::activate() {
    life = 1.0f;
    fade = 0.05f + F_RAND() * 0.4f;

    posX = posY = posZ = 0.0f;
    posX = 10.0f;
    posY = -5.0f;
    posZ = 10.0f;

}

void Spaceship::live(float tt) {
    posX += movX * tt;
    posY += movY * tt;
    posZ += movZ * tt;

    movX += gravX * tt;
    movY += gravY * tt;
    movZ += gravZ * tt;

    life -= fade * tt;

    if (life <= 0.0f) activate();

}

void Spaceship::Render() const {

//    glClear(GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();

    // Draw the spaceship
    glPushMatrix();
    draw();
    glPopMatrix();

//    glutSwapBuffers();

}

void Spaceship::setPos(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Spaceship::move(float x, float y, float z) {
    posX += x;
    posY += y;
    posZ += z;
}

void Spaceship::draw() const {
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex3f(posX - 10.0f, posY - 10.0f, posZ); // Bottom left
    glVertex3f(posX + 10.0f, posY - 10.0f, posZ); // Bottom right
    glVertex3f(posX + 10.0f, posY + 10.0f, posZ); // Top right
    glVertex3f(posX - 10.0f, posY + 10.0f, posZ); // Top left
    glEnd();

    // Draw the wings of the spaceship
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex3f(posX - 15.0f, posY, posZ); // Left wing
    glVertex3f(posX - 10.0f, posY - 10.0f, posZ); // Bottom left
    glVertex3f(posX - 10.0f, posY + 10.0f, posZ); // Top left

    glVertex3f(posX + 15.0f, posY, posZ); // Right wing
    glVertex3f(posX + 10.0f, posY - 10.0f, posZ); // Bottom right
    glVertex3f(posX + 10.0f, posY + 10.0f, posZ); // Top right
    glEnd();

    glPopMatrix();
}