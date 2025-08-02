#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    // default constructor, we'll just initialize the eye, up and view_dir vectors 
    Camera();

    glm::mat4 getViewMat();
    // { put this int the .cpp file
    //     return glm::lookAt(this->eye, this->view_dir, this->up);
    // }

    // @params: the amount to move
    void move_left(float amount); 
    void move_right(float amount);
    void move_forwards(float amount);
    void move_backwards(float amount);

    // rotate along the normal 
    void rotate(float dx, float dy, float dt);

private:
    glm::vec3 eye;      // position of camera
    glm::vec3 view_dir; // direction of viewing 
    glm::vec3 up;       // normal 
};

#endif