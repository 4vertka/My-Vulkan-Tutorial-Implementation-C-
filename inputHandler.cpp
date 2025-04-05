#include "./inputHandler.hpp"

InputHandler::InputHandler(GLFWwindow *window, Camera *camera)
    : window(window), camera(camera), lastX(0.0f), lastY(0.0f),
      firstMouse(true), deltaTime(0.0f), lastFrame(0.0f) {
  // Center the cursor position for first use
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  lastX = width / 2.0f;
  lastY = height / 2.0f;

  // Set the mouse callback
  glfwSetWindowUserPointer(window, this);
  glfwSetCursorPosCallback(window, mouseMoveCallback);

  // Capture the cursor
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputHandler::processInput() {
  // Calculate delta time
  float currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // Process keyboard input
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // WASD movement
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->processKeyboard(Camera::FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->processKeyboard(Camera::BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->processKeyboard(Camera::LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->processKeyboard(Camera::RIGHT, deltaTime);

  // F for up, shift+F for down
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      camera->processKeyboard(Camera::DOWN, deltaTime);
    else
      camera->processKeyboard(Camera::UP, deltaTime);
  }
}

void InputHandler::mouseMoveCallback(GLFWwindow *window, double xpos,
                                     double ypos) {
  InputHandler *handler =
      static_cast<InputHandler *>(glfwGetWindowUserPointer(window));
  handler->processMouseMovement(xpos, ypos);
}

void InputHandler::processMouseMovement(double xpos, double ypos) {
  if (firstMouse) {
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);
    firstMouse = false;
    return; // added
  }

  // float xoffset = static_cast<float>(xpos) - lastX;
  float xoffset = static_cast<float>(xpos) - lastX;

  // float xoffset = lastX - static_cast<float>(xpos);
  // float yoffset = lastY - static_cast<float>(ypos); // Reversed: y ranges
  //  bottom to top

  // float yoffset = static_cast<float>(ypos) - lastY;
  float yoffset = lastY - static_cast<float>(ypos);

  lastX = static_cast<float>(xpos);
  lastY = static_cast<float>(ypos);

  camera->processMouseMovement(xoffset, yoffset);
}
