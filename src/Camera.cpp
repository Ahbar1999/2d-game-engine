#define GLM_ENABLE_EXPERIMENTAL 
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

// initializes
// eye to origin
// view_dir to negative z axis, i.e. into the screen
// up vector to +y axis; 

Camera::Camera() {
    this->eye = glm::vec3(0.0f, 0.0f, 1.0f);
    this->view_dir = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0);
};

// just modify the director vecotr
void Camera::rotate(float dx, float dy, float dt) {
    this->view_dir = glm::rotate(this->view_dir, glm::radians(dx * dt), this->up); 
}

glm::mat4 Camera::getViewMat() {
    // construct the matrix from our vectors 
    return glm::lookAt(this->eye, this->eye + this->view_dir, this->up);
}

void Camera::move_forwards(float amount) {
    this->eye.z -= amount;
}

void Camera::move_backwards(float amount) {
    this->eye.z += amount;
}

void Camera::move_left(float amount) {
    this->eye.x -= amount; 
}

void Camera::move_right(float amount) {
    this->eye.x += amount; 
}