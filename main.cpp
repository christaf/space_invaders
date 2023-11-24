#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Game state
bool gameStarted = false;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        gameStarted = true;
    }
}

void drawStartScreen(GLFWwindow *window) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw start screen elements
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.5f, 0.0f);
    const char *text = "Press SPACE to start";
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
    }

    glfwSwapBuffers(window);
}

void drawGame(GLFWwindow *window) {
    // Draw game elements
    // ...

    glfwSwapBuffers(window);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Space Invaders", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        if (gameStarted) {
            drawGame(window);
        } else {
            drawStartScreen(window);
        }

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}