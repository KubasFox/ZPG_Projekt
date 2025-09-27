#include "Game.h"

Game::Game() : window(nullptr) {}

Game::~Game() {
    cleanup();
}

bool Game::initialize() {
    //inicializace glfw
    if (!glfwInit()) { std::cerr << "Failed to initialize GLFW" << std::endl; return false;}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //window creation
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ZPG Projekt", nullptr, nullptr);
    if (!window) { std::cerr << "Failed to create GLFW window" << std::endl; glfwTerminate(); return false;}
    glfwMakeContextCurrent(window);

    //inicializace glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) { std::cerr << "Failed to initialize GLEW" << std::endl; return false; }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);

    if (!setupScene()) { std::cerr << "Failed to setupScene" << std::endl; return false ;}
    std::cout << "Game initialized successfully!" << std::endl;
    return true;
}


bool Game::setupScene() {
    drawableObject2.importData({
        0.0f,  0.3f, 0.0f,
       -0.5f, -0.7f, 0.0f,
        0.5f, -0.7f, 0.0f
        },{ 0, 1, 2 },{
        0.5f, 1.0f,
        0.0f, 0.99f,
        1.0f, 0.99f});
    drawableObject2.changeShader("Default.vert", "Second.frag");

    if (!drawableObject2.build()) {return false;}
    if (!drawableObject.build()) { return false; }
    return true;
}


void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        update();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


void Game::render() {
    drawableObject.render();
    drawableObject2.render();
}


void Game::update() {

}


void Game::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


void Game::cleanup() {
    drawableObject.cleanup();
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}


void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_SPACE:
            std::cout << "Space" << std::endl;
            break;
        }
    }
}


void Game::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            std::cout << "Left" << std::endl;
            break;
        }
    }
}