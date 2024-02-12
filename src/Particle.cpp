//
// Created by mateu on 12/02/2024.
//

#include "Particle.h"
#include "GL/freeglut.h "
#include "stdlib.h"
#include <cmath>

#define _USE_MATH_DEFINES

#define F_RAND() ((float)rand()/RAND_MAX)

Particle::~Particle() {}

Particle::Particle() {
    activate();

    r = 1.0f;
    g = F_RAND();
    b = F_RAND();

    active = false;
    size = F_RAND() * 5.0f + 0.5f;
}

void Particle::activate() {
    life = 1.0f;
    fade = 0.05f + F_RAND() * 0.4f;

    posX = posY = posZ = 0.0f;
    posX = 10.0f;
    posY = -5.0f;
    posZ = 10.0f;


    double fi = M_PI / 4;
    double psi = F_RAND() * (M_PI * 2);
    double rr = F_RAND() * 12 + 16;

    movX = rr * cos(fi) * cos(psi);
    movY = rr * sin(fi);
    movZ = rr * cos(fi) * sin(psi);

    gravX = gravZ = 0;
    gravY = -10;
}

void Particle::live(float tt) {
    posX += movX * tt;
    posY += movY * tt;
    posZ += movZ * tt;

    movX += gravX * tt;
    movY += gravY * tt;
    movZ += gravZ * tt;

    life -= fade * tt;

    if (life <= 0.0f) activate();
}

void Particle::Render() const {

    glPushMatrix();

    glColor4f(r, g, b, fade);
    glTranslated(posX, posY, posZ);
    glRotated(1.0, 1.0, 1.0, 0.0);

    glutSolidSphere(size, 15, 15);
    /*
    glPointSize(size * 2);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();
    */
    glPopMatrix();
}
