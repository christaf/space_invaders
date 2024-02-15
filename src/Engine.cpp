
#include <cstdlib>
#include "GL/glew.h"
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include "Particle.h"
#include "Bullet.h"
#include "Spaceship.h"

#define MAX_PART 1000
#define ACTIVATE_TIME 0.1

class Engine {
private:
    Particle **particles;
    float angleY;
    float angleSpeed;
    Bullet **bullets;
    Spaceship *spaceship;
    bool isSpacePressed = false;

public:
    Engine() {
        particles = new Particle *[MAX_PART];
        bullets = new Bullet *[MAX_PART];
        for (int i = 0; i < MAX_PART; i++) {
            particles[i] = new Particle();
        }
        for (int i = 0; i < MAX_PART; i++) {
            bullets[i] = new Bullet();
        }
        spaceship = new Spaceship();
        angleY = 0;
        angleSpeed = 0.5;
    }

    ~Engine() {
        for (int i = 0; i < MAX_PART; i++) {
            delete particles[i];
        }
        delete[] particles;
    }

    static void init() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glClearColor(1, 1, 1, 1);

        //Face culling
        glFrontFace(GL_CW);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        //perspectiveGL(100,1,1,1000);

        gluPerspective(100, 1, 1, 1000); //FOV

        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_BLEND);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void update(int value) {
        angleY += angleSpeed;

        // Shoot bullet if spacebar is pressed

//        for(int i = 0; i < MAX_PART; i++) {
//            particles[i]->live(ACTIVATE_TIME);
//        }

//        spaceship->live(ACTIVATE_TIME);
        if (isSpacePressed) {
            for (int i = 0; i < MAX_PART; i++) {
                if (bullets[i] == nullptr) {
//                    bullets[i] = new Bullet();
                } else {
//                    if(!bullets[i]->active) {
                    bullets[i]->live(ACTIVATE_TIME);
//                    }
                }
            }
        }


        glutPostRedisplay();
        glutTimerFunc(10, staticUpdateWrapper, 0);
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(20, 20, 0, 0, 1, 0, 0, 1, 0);

        // Render particles
//        for (int i = 0; i < MAX_PART; i++) {
//            glPushMatrix();
//            glRotatef(angleY, 0, 1, 0);
//            particles[i]->Render();
//            glPopMatrix();
//        }
        fireBullet();
        spaceship->Render();

        glFlush();
        glutSwapBuffers();
    }

    void fireBullet() {
        glPushMatrix();
        bullets[0]->Render();
        glPopMatrix();
    }

    static void staticDisplayWrapper() {
        instance->display();
    }

    static void staticUpdateWrapper(int value) {
        instance->update(value);
    }

    static void handleKeypress(unsigned char key, int x, int y) {

        switch (key) {
            case 'w':
                instance->spaceship->move(0, 0, 1);
                break;
            case 's':
                instance->spaceship->move(0, 0, -1);
                break;
            case 'a':
                instance->spaceship->move(-1, 0, 0);
                break;
            case 'd':
                instance->spaceship->move(1, 0, 0);
                break;
            case ' ':
                instance->isSpacePressed = true;
                break;
        }
    }

    static void handleKeyRelease(unsigned char key, int x, int y) {
        if (key == ' ') {
            instance->isSpacePressed = false;
        }
    }

    static void run() {
        init();
        glutDisplayFunc(staticDisplayWrapper);
        glutKeyboardFunc(handleKeypress);
        glutKeyboardUpFunc(handleKeyRelease);
        glutTimerFunc(10, staticUpdateWrapper, 0);
        glutMainLoop();
    }

    static Engine *instance;
};