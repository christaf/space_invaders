//
// Created by mateu on 12/02/2024.
//

#include <GL/glew.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

std::string LoadTextFile(std::string fileName) {
    std::ifstream plix;
    plix.open(fileName, std::ios::in);
    if (!plix.is_open()) {
        std::cout << "Open file error: " << fileName << std::endl;
        system("pause");
        exit(0);
    }
    // Odczyt calosci pliku:
    std::string line, buff;
    while (!plix.eof()) {
        getline(plix, line);
        buff += line + "\n";
    }
    return(buff);
}

// Sprawdzenie b��d�w linkowania:
bool CheckLinkErrors(GLuint prog) {
    int res, logLen;
    char buff[1024];

    glGetProgramiv(prog, GL_LINK_STATUS, &res);
    if (res == GL_FALSE) {
        cout << "GL_LINK_STATUS ERROR!" << endl;
        glGetProgramInfoLog(prog, 1024, &logLen, buff);
        cout << buff << endl;
        return(false);
    }
    return(true);
}
// Sprawdzenie b��d�w kompilacji:
bool CheckCompileErrors(GLuint shad) {
    int res, logLen;
    char buff[1024];

    glGetShaderiv(shad, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        cout << "GL_COMPILE_STATUS ERROR!" << endl;
        glGetShaderInfoLog(shad, 1024, &logLen, buff);
        cout << buff << endl;
        return(false);
    }
    return(true);
}


void drawRoom(float position[3], float width, float height, float depth){
    float vertices[8][7] =
            {
                    {position[0]-width, position[1]-height, position[2]+depth, 1, 0, 0, 1},
                    {position[0]-width, position[1]+height, position[2]+depth, 0, 1, 0, 1},
                    {position[0]+width, position[1]+height, position[2]+depth, 0, 0, 1, 1},
                    {position[0]+width, position[1]-height, position[2]+depth, 1, 1, 0, 1},
                    {position[0]-width, position[1]-height, position[2]-depth, 1, 0, 1, 1},
                    {position[0]-width, position[1]+height, position[2]-depth, 0, 1, 1, 1},
                    {position[0]+width, position[1]+height, position[2]-depth, 1, 1, 0, 1},
                    {position[0]+width, position[1]-height, position[2]-depth, 0, 0, 0, 1}
            };
    int indices[] =
                  {
                            2, 6, 7, 3,
                            0, 1, 2, 3,
                            3, 7, 4, 0,
                            5, 1, 2, 6,
                            5, 4, 7, 6,
                            0, 4, 5, 1

                  };

    GLuint vertexBufferHandle = 0;
    glGenBuffers(1, &vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indexBufferHandle = 0;
    glGenBuffers(1, &indexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, indexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*
    GLuint colourBufferHandle = 0;
    glGenBuffers(1, &colourBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, colourBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colourBufferHandle), colours, GL_STATIC_DRAW);
     */

    GLuint ObjectVAO;
    GLuint ShaderProgram;

    // Przygotowanie VAO:
    glGenVertexArrays(1, &ObjectVAO);
    glBindVertexArray(ObjectVAO);

    // Index 0 -> wierzcholki:
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // Odblokowanie atrybutow nr 0 i 1:
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // Wczytanie kodu shader�w z plik�w:
    std::string VertSource = LoadTextFile("VertexShader.vertexshader");
    std::string FragSource = LoadTextFile("FragmentShader.fragmentshader");
    const char* src[1];

    // Inicjalizacja shader�w:
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    src[0] = VertSource.c_str();
    glShaderSource(vs, 1, src, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    src[0] = FragSource.c_str();
    glShaderSource(fs, 1, src, NULL);
    glCompileShader(fs);

    if (!CheckCompileErrors(vs) || !CheckCompileErrors(fs)) {
        cout << "Shader compile error!" << endl;
        system("pause");
        exit(0);
    }

    // Utworzenie programu i poloczenie:
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, fs);
    glAttachShader(ShaderProgram, vs);
    glLinkProgram(ShaderProgram);

    if (!CheckLinkErrors(ShaderProgram)) {
        cout << "Shader linking error!" << endl;
        system("pause");
        exit(0);
    }

    glUseProgram(ShaderProgram);
}


/*
void drawRoom(float c[3], float width, float height, float depth){
    float w = width;
    float h = height;
    float d = depth;

    float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]+d},   {c[0]-w,c[1]+h,c[2]+d},   {c[0]+w,c[1]+h,c[2]+d},   {c[0]+w,c[1]-h,c[2]+d},
                             {c[0]-w,c[1]-h,c[2]-d},    {c[0]-w,c[1]+h,c[2]-d},   {c[0]+w,c[1]+h,c[2]-d},   {c[0]+w,c[1]-h,c[2]-d}};

    glNormal3f(0,0,1);
    glBegin(GL_POLYGON);
    glColor4f(1,0,0,1);
    glVertex3fv(verticies[2]);
    glVertex3fv(verticies[6]);
    glVertex3fv(verticies[7]);
    glVertex3fv(verticies[3]);
    glEnd();

    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    //glColor3f(0.3,0.2,1);
    glVertex3fv(verticies[0]);
    glVertex3fv(verticies[1]);
    glVertex3fv(verticies[2]);
    glVertex3fv(verticies[3]);
    glEnd();

    glNormal3f(-1,0,0);
    glBegin(GL_POLYGON);
//	glColor3f(0.2,0.2,.9);
    glVertex3fv(verticies[3]);
    glVertex3fv(verticies[7]);
    glVertex3fv(verticies[4]);
    glVertex3fv(verticies[0]);
    glEnd();

    glNormal3f(1,0,0);
    glBegin(GL_POLYGON);
    //glColor4f(0.2,0.1,1,0.1);
    glVertex3fv(verticies[5]);
    glVertex3fv(verticies[1]);
    glVertex3fv(verticies[2]);
    glVertex3fv(verticies[6]);
    glEnd();

    glNormal3f(0,0,1);
    glBegin(GL_POLYGON);
    //glColor3f(0.2,0.2,.8);
    glVertex3fv(verticies[5]);
    glVertex3fv(verticies[4]);
    glVertex3fv(verticies[7]);
    glVertex3fv(verticies[6]);
    glEnd();

    glNormal3f(0,-1,0);
    glBegin(GL_POLYGON);
    //glColor3f(0.2,0.2,1);
    glVertex3fv(verticies[0]);
    glVertex3fv(verticies[4]);
    glVertex3fv(verticies[5]);
    glVertex3fv(verticies[1]);
    glEnd();
}
 */