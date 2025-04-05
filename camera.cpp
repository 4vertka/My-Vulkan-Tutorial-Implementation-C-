#include "./camera.hpp"
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane) {
  position = glm::vec3(0.0f, 0.0f, 5.0f); // Default position
  // position = glm::vec3(2.0f, 2.0f, 2.0f); // Default position
  front = glm::vec3(0.0f, 0.0f, -1.0f); // Looking down -Z
  // front = glm::vec3(-2.0f, -2.0f, -2.0f); // Looking down -Z
  up = glm::vec3(0.0f, 1.0f, 0.0f); // Up is +Y
  // up = glm::vec3(0.0f, 0.0f, 1.0f); // Up is +Y
  worldUp = up;

  movementSpeed = 2.5f;    // Units per second
  mouseSensitivity = 0.1f; // Degrees per pixel

  yaw = -90.0f; // Default yaw (facing -Z)
  pitch = 0.0f; // Default pitch (horizontal)

  viewMatrix = glm::lookAt(position, position + front, up);
  projectionMatrix =
      glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
  projectionMatrix[1][1] *= -1;
}

glm::mat4 Camera::getViewMatrix() const { return viewMatrix; }

glm::mat4 Camera::getProjectionMatrix() const { return projectionMatrix; }

glm::vec3 Camera::getPosition() const { return position; }

glm::vec3 Camera::getFront() const { return front; }

void Camera::updateViewMatrix() {
  viewMatrix = glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
  float velocity = movementSpeed * deltaTime;

  if (direction == FORWARD)
    position += front * velocity;
  if (direction == BACKWARD)
    position -= front * velocity;
  if (direction == LEFT)
    position -= glm::normalize(glm::cross(front, up)) * velocity;
  if (direction == RIGHT)
    position += glm::normalize(glm::cross(front, up)) * velocity;
  if (direction == UP)
    position += up * velocity;
  if (direction == DOWN)
    position -= up * velocity;

  updateViewMatrix();
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch += yoffset;

  // Constrain pitch to avoid camera flipping
  if (constrainPitch) {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }

  // Update front, right and up vectors
  updateCameraVectors();
}

void Camera::setProjection(float fov, float aspectRatio, float nearPlane,
                           float farPlane) {
  projectionMatrix =
      glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::updateCameraVectors() {
  // Calculate the new front vector
  glm::vec3 newFront;
  newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  newFront.y = sin(glm::radians(pitch));
  newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(newFront);

  // Recalculate the right and up vectors
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));

  updateViewMatrix();
}
