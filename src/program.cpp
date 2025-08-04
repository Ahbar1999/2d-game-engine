#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.h"
#include "ResourceManager.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_cursor_callback(GLFWwindow* window , double xpos, double ypos);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game THEGame(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    glfwSetCursorPosCallback(window, mouse_cursor_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // OpenGL configuration
    // --------------------
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);
    // glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    THEGame.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // glfwSetCursorPos(window, 1.0 * SCREEN_HEIGHT / 2.0, 1.0 * SCREEN_WIDTH / 2.0);
    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        THEGame.ProcessInput(deltaTime);

        // update game state
        // -----------------
        THEGame.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        THEGame.Render(deltaTime);

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            THEGame.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            THEGame.Keys[key] = false;
    }
}

void mouse_cursor_callback(GLFWwindow* window , double xpos, double ypos) {
    static bool first_call = 1;
    if (first_call) {
        first_call =0;
        THEGame.mouse_x = xpos;
        THEGame.mouse_y = ypos;  
    }
     
    THEGame.mouse_dx = THEGame.mouse_x - xpos;
    THEGame.mouse_dy = THEGame.mouse_y - ypos;
    if (std::abs(THEGame.mouse_dx) <= 1) {
        THEGame.mouse_dx = 0;
    }

    if (std::abs(THEGame.mouse_dy) <= 1) {
        THEGame.mouse_dy = 0;
    }
    
    THEGame.mouse_x = xpos;
    THEGame.mouse_y = ypos;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}