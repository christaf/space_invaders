//
// Created by mateu on 15.02.2024.
//

#include "Bullet.h"
#include "GL/freeglut.h "
#include <cstdlib>
#include <cmath>

#define USE_MATH_DEFINES

#define F_RAND() ((float)rand()/RAND_MAX)

Bullet::~Bullet() = default;

Bullet::Bullet(float start_x, float start_y, float start_z) {

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

void Bullet::activate() {
    life = 1.0f;
    active = true;
    fade = 0.05f + F_RAND() * 0.4f;

    movX = 0;
    movY = 10;
    movZ = 0;

    gravX = gravZ = 0;
    gravY = -10;
}

void Bullet::live(float tt) {
//    posX += movX * tt;
    posY += movY * tt;
//    posZ += movZ * tt;

//    movX += gravX * tt;
//    movY += gravY * tt;
//    movZ += gravZ * tt;

    life -= fade * tt;

    if (life <= 0.0f) active = false;
}

void Bullet::Render() const {
    glPushMatrix();

    glColor4f(r, g, b, fade);
    glTranslated(posX, posY, posZ);
    glRotated(1.0, 1.0, 1.0, 0.0);

    // Draw a cube
//    glutSolidCylinder(0.5, 1, 10, 10);

    glPointSize(size * 2);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();

    glPopMatrix();
}

Bullet::Bullet() {
    posX = 0;
    posY = 0;
    posZ = 0;

    active = false;
    activate();

    r = 1.0f;
    g = F_RAND();
    b = F_RAND();

    size = F_RAND() * 5.0f + 0.5f;

}
