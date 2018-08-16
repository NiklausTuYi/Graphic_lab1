//
// Created by Yi Tu on 2018/2/25.
//
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    ROTATE_UP,
    ROTATE_DOWN
};
class Camera
{
private:
    GLuint screenWidth, screenHeight;
    Camera(){
        this->eye = glm::vec3();
        this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    Camera(const Camera &);
    Camera & operator = (const Camera &);

public:
    glm::vec3 eye, worldUp,  center, up, right;
    GLfloat yaw = -90, pitch = -30.0f, angle = 0.0f;

    glm::mat4 camera_mat;

    static Camera & Get(){
        static Camera thisCamera = Camera();
        return thisCamera;
    }

    void set(glm::vec3 eys_position, GLuint screenWidth, GLuint screenHeight){
        this->eye = eys_position;
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->center = glm::normalize(front);
        this->right = glm::normalize(glm::cross(this->center, this->worldUp));
        this->up = glm::normalize(glm::cross(this->right, this->center));
    }

    glm::mat4 GetMatrix(){
        camera_mat= glm::lookAt(this->eye, this->eye + this->center, this->up);
        camera_mat = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f)*camera_mat;
        return camera_mat;
    }

    void move(Camera_Movement direction, GLfloat deltaTime){
        GLfloat velocity = 30 * deltaTime;

        if (direction == ROTATE_LEFT)
            this->center += glm::vec3(0.06*sin(-0.1),0,0);
        if (direction == ROTATE_RIGHT)
            this->center += glm::vec3(0.06*sin(0.1),0,0.0);
        if (direction == ROTATE_UP)
            this->center += glm::vec3(0,0.06*cos(0.1),0);
        if (direction == ROTATE_DOWN)
            this->center += glm::vec3(0,-0.06*cos(0.1),0);
        if (direction == FORWARD)
            eye += center * velocity;
        if (direction == BACKWARD)
            eye -= center * velocity;
        if (direction == LEFT)
            eye -= right * velocity;
        if (direction == RIGHT)
            eye += right * velocity;

    }
};
