#include <cstdlib>
#include "glew-2.2.0/include/GL/glew.h"
#include <GL/freeglut.h>
//#include "glut.h"
#include <cmath>
#include <GLFW/glfw3.h>
#include "Particle.h"
#include "shapes.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/vec3.hpp"

#define MAX_PART 1000
#define ACTIVATE_TIME 0.1


Particle** part;
float ambientLight[4] = { .1, .1, .1, 1.0 };
float diffuseLight[4] = { 0.5, 0.4,0.6, 1.0 };
float specularLight[4] = { 1, 1, 1, 1.0 };
float lightPos[4] = { 5, 5, 5, 1 };
float roomPos[3] = {0,-21,0};

float angleY = 0;
float angleSpeed = 0.5;


void light(){
	float lightPos2[4] = {5,20,0,1};
	float light2Dir[3] = {0,0,0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

/*
void lookAt(glm::vec3 Eye, glm::vec3 At, glm::vec3 Up){
    //Vector3 Eye, At, Up; //these should be parameters =)

    glm::vec3 zaxis = At - Eye; zaxis = glm::normalize(zaxis);
    //Vector3 zaxis = At - Eye; zaxis.Normalize();

    glm::normalize(Up);
    //Up.Normalize();

    glm::vec3 xaxis = glm::cross(Up, zaxis);  xaxis = glm::normalize(xaxis);
    //Vector3 xaxis = Vector3::Cross(Up, zaxis);  xaxis.Normalize();

    glm::vec3 yaxis = glm::cross(zaxis, xaxis);   yaxis = glm::normalize(yaxis);
    //Vector3 yaxis = Vector3::Cross(zaxis, xaxis);   yaxis.Normalize();

    float r[16] =
            {
                    xaxis.x,    yaxis.x,    -zaxis.x,    0,
                    xaxis.y,    yaxis.y,    -zaxis.y,    0,
                    xaxis.z,    yaxis.z,    -zaxis.z,    0,
                    0,          0,          0,          1,
            };
    glm::mat4 Rotation;
    //Matrix Rotation;
    memcpy(Rotation.values, r, sizeof(r));

    float t[16] =
            {
                    1,      0,      0,     0,
                    0,      1,      0,     0,
                    0,      0,      1,     0,
                    -Eye.x, -Eye.y, -Eye.z, 1,
            };

    glm::mat4 Translation;
    //Matrix Translation;
    memcpy(Translation.values, t, sizeof(t));


    View = Rotation * Translation;
}
 */

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    light();
    glLoadIdentity();
    gluLookAt(20,20,-45,0,1,0,0,1,0);
    /*
    glm::lookAtRH(glm::vec3(2.0f, 2.0f, -45.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f));
                  */

    /*
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(1.0f, 1.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
                       */

    //

    /*
    glRotatef(angleY,0,1,0);
    glPushMatrix();
    //drawRoom(roomPos,25,2,25);
    glPopMatrix();
     */
    drawRoom(roomPos,25,2,25);
    for (int i = 0; i < MAX_PART; i++){
        glPushMatrix();
        glRotatef(angleY,0,1,0);
        part[i]->Render();
        glPopMatrix();
    }
    glFlush();
    glutSwapBuffers();
}

void update(int value){

    angleY+= angleSpeed;
    for (int i = 0; i < MAX_PART; i++){
        part[i]->live(0.1f);
        /*
        if (part[i]->active) {
            part[i]->live(0.5f);
        }
        else {
            //if(act_time >= ACTIVATE_TIME)
            part[i]->activate();
        }
         */
    }
    glutPostRedisplay();
    glutTimerFunc(10,update,0);
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    GLdouble fW, fH;

    fH = tan( fovY / 360 * M_PI ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void init(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(1,1,1,1);

    //Face culling
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    //perspectiveGL(100,1,1,1000);

    gluPerspective(100,1,1,1000);//FOV

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable (GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
int main(int argc, char** argv)
{
    part = new Particle*[MAX_PART];

    for (int i = 0; i < MAX_PART; i++){
        part[i] = new Particle();
    }

    glutInit(&argc, argv);		//starts up GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280,720);
    glutCreateWindow("Particle Fountain");	//creates the window
    glutDisplayFunc(display);
    init();

    glutTimerFunc(100, update, 0);

    glutMainLoop();

    return(0);
}