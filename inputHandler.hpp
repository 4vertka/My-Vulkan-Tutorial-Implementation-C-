#pragma once

#include "./camera.hpp"
#include <GLFW/glfw3.h>

class InputHandler {
public:
    InputHandler(GLFWwindow* window, Camera* camera);
    
    void processInput();
    
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    
private:
    GLFWwindow* window;
    Camera* camera;
    
    // Mouse tracking
    float lastX;
    float lastY;
    bool firstMouse;
    
    // Timing
    float deltaTime;
    float lastFrame;
    
    void processMouseMovement(double xpos, double ypos);
};
