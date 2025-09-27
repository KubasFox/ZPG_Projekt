#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "DrawableObject.h"


class Game {
private:
    GLFWwindow* window;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    
    DrawableObject drawableObject;
    DrawableObject drawableObject2;

    bool setupScene();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);

public:
    Game();
    ~Game();

    bool initialize();
    void run();
    void processInput();
    void update();
    void render();
    void cleanup();
};

#endif