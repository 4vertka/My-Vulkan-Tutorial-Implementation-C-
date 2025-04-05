#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    // Define movement directions
    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // Constructor
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    // Getters
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;

    // Camera controls
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    
    // Update camera properties
    void setProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

private:
    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    // Camera matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    // Euler angles
    float yaw;
    float pitch;
    
    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    
    // Helper methods
    void updateCameraVectors();
    void updateViewMatrix();
};
