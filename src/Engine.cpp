//
// Created by mateu on 24.11.2023.
//

#include "Engine.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/freeglut.h>

class Engine {
public:

    enum class GameState {
        StartScreen,
        Game,
    };

    Engine(int width, int height, const char *title)
            : width(width), height(height), title(title) {
        gameState = GameState::StartScreen;
    }

    void run(int *argc, char **argv) {
        if (!init()) {
            std::cerr << "Failed to initialize GLFW\n";
            return;
        }

        glutInit(argc, argv);
        glfwSetWindowUserPointer(window, this);

        glfwSwapInterval(1);  // Enable vertical synchronization

        double lastTime = glfwGetTime();
        const double targetFrameRate = 60.0;
        const double frameTime = 1.0 / targetFrameRate;

        while (!glfwWindowShouldClose(window)) {
            double currentTime = glfwGetTime();
            double deltaTime = currentTime - lastTime;

            if (deltaTime >= frameTime) {
                lastTime = currentTime;

                glfwPollEvents();
                update();
                render();
            }
        }

        cleanup();
    }

private:
    int width;
    int height;
    const char *title;
    GLFWwindow *window{};
    GameState gameState;

    bool init() {
        if (!glfwInit()) {
            return false;
        }

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!window) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);

        return true;
    }

    void update() {
        // Game logic update
    }

    void render() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (gameState == GameState::StartScreen) {
            drawStartScreen();
        } else if (gameState == GameState::Game) {
            drawGame();
        }

        glfwSwapBuffers(window);
    }

    static void cleanup() {
        glfwTerminate();
        glutLeaveMainLoop();
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *engine = static_cast<Engine *>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->handleKey(key, action);
        }
    }

    void handleKey(int key, int action) {
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            if (gameState == GameState::StartScreen) {
                gameState = GameState::Game;
                std::cout << "Game started\n";
            }
        }
    }

    void drawStartScreen() {
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

    void drawGame() {
        glClearColor(0.5f, 0.0f, 1.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 0.0f, 1.0f);
        glRasterPos2f(-0.5f, 0.0f);
        const char *text = "GAME UHAHAHHA";
        while (*text) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
        }

        // Draw game elements
        // ...

        glfwSwapBuffers(window);
    }
};
