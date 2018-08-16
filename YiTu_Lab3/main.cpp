#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Model.h"

using namespace std;

const GLuint screenWidth = 1200, screenHeight = 1200;
glm::mat4 cameraMatrix;
glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
glm::mat4 Model::viewMatrix = glm::mat4();
Model * object[3];

GLfloat startTime;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


bool keys[1024] = { false };
bool start = false;

void init(){
    Camera::Get().set(eye, screenWidth, screenHeight);

    Light::add(glm::vec3(10.0, 16, 10.0), glm::vec3(1.0, 1.0, 1.0));
    Light::add(glm::vec3(30.0, 16, -30.0), glm::vec3(1.0, 1.0, 1.0));
    Light::add(glm::vec3(-5.0, 16, 10.0), glm::vec3(1.0, 1.0, 1.0));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;

    if (start == false) {
        //If P pressed, start animation.
        if (key == GLFW_KEY_P) {
            start = true;
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

}

void move()
{
    // Object controls
    if (keys[GLFW_KEY_W])
        object[0]->position = object[0]->position + glm::vec3( 0.0f, 0.0f, -1.0f);
    if (keys[GLFW_KEY_S])
        object[0]->position = object[0]->position + glm::vec3( 0.0f, 0.0f, 1.0f);
    if (keys[GLFW_KEY_A])
        object[0]->position = object[0]->position + glm::vec3( -1.0f, 0.0f, 0.0f);
    if (keys[GLFW_KEY_D])
        object[0]->position = object[0]->position + glm::vec3( 1.0f, 0.0f, 0.0f);
    if (keys[GLFW_KEY_8])
        object[0]->scaleDegree *= glm::vec3( 1.2f, 1.2f, 1.2f);
    //object[0]->position.y += 1.2f*3.8f;
    if (keys[GLFW_KEY_9])
        object[0]->scaleDegree *= glm::vec3( 0.8f, 0.8f, 0.8f);
    //object[0]->position.y = object[0]->position - 0.8f*glm::vec3(0.0f, 3.8f, 0.0f);
    if (keys[GLFW_KEY_Q])
        object[0]->rotationDegree += 10.0f;
    if (keys[GLFW_KEY_E])
        object[0]->rotationDegree -= 10.0f;

    // Camera controls
    if (keys[GLFW_KEY_UP])
        Camera::Get().move(FORWARD, deltaTime);
    if (keys[GLFW_KEY_DOWN])
        Camera::Get().move(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_LEFT])
        Camera::Get().move(LEFT, deltaTime);
    if (keys[GLFW_KEY_RIGHT])
        Camera::Get().move(RIGHT, deltaTime);
    if (keys[GLFW_KEY_J])
        Camera::Get().move(ROTATE_LEFT, deltaTime);
    if (keys[GLFW_KEY_L])
        Camera::Get().move(ROTATE_RIGHT, deltaTime);
    if (keys[GLFW_KEY_I])
        Camera::Get().move(ROTATE_UP, deltaTime);
    if (keys[GLFW_KEY_K])
        Camera::Get().move(ROTATE_DOWN, deltaTime);
}

void animation(){
    object[0]->position = object[0]->position + glm::vec3( glm::sin((glfwGetTime() - startTime)*3),0.0f, 0.0f);
    object[1]->position = object[1]->position + glm::vec3( 0.0f, 0.1 * glm::cos(glfwGetTime() - startTime)*3,0.0f);
    object[2]->position = object[2]->position + glm::vec3( 0.5 * glm::sin((glfwGetTime() - startTime)*3),0.0f, 0.2 * glm::cos(glfwGetTime() - startTime)*3);
}

int main() {
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "YiTu_Lab3", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, 1200, 1200);

    glEnable(GL_CULL_FACE);

    init();


    //create models
    Model floor((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/ground.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/brickpic.png", true);
    Model ceiling((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/ground.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/bricks.png", true);
    Model * walls[3];

    floor.position = glm::vec3(0.0f, 0.0f, 0.0f);
    floor.rotationDegree = 0.0f;

    ceiling.position = glm::vec3(0.0f, 20.0f, 0.0f);
    ceiling.rotationDegree = 0.0f;


    walls[0] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/bricks.png", true);
    walls[1] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/bricks.png", true);
    walls[2] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/bricks.png", true);
    walls[3] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/bricks.png", true);

    walls[0]->position = glm::vec3(0.0f, 0.0f, -40.0f);
    walls[0]->rotationDegree = 0.0f;
    walls[0]->scaleDegree = glm::vec3(1.0f, 2.0f, 1.0f);


    walls[1]->position = glm::vec3(0.0f, 0.0f, 40.0f);
    walls[1]->rotationDegree = 0.0f;
    walls[1]->scaleDegree = glm::vec3(1.0f, 2.0f, 1.0f);

    walls[2]->position = glm::vec3(40.0f, 0.0f, 0.0f);
    walls[2]->rotationDegree = 90.0f;
    walls[2]->scaleDegree = glm::vec3(1.0f, 2.0f, 1.0f);

    walls[3]->position = glm::vec3(-40.0f, 0.0f, 0.0f);
    walls[3]->rotationDegree = -90.0f;
    walls[3]->scaleDegree = glm::vec3(1.0f, 2.0f, 1.0f);


    object[0] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/cow.d", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/solidcolor2.png", true);
    object[0]->position = glm::vec3(0.0f, 3.8f, 0.0f);
    object[0]->rotationDegree = 0.0f;
    object[0]->scaleDegree = glm::vec3(1.5f, 1.5f, 1.5f);

    object[1] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/cow.d", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/solidcolor1.png", false);
    object[1]->position = glm::vec3(-20.0f, 0.0f, -20.0f);
    object[1]->rotationDegree = 45.0f;
    object[1]->scaleDegree = glm::vec3(2.0f, 2.0f, 2.0f);

    object[2] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/duck.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/data/duck_upsidedown.png", true);
    object[2]->position =  glm::vec3(20.0f, 3.8f, 20.0f);
    object[2]->rotationDegree = 0.0f;
    object[2]->scaleDegree = glm::vec3(0.04f, 0.04f, 0.04f);


    //after all models built, set up the drawer, create the image
    std::cout << "Press P to Start Animation!" << std::endl;
    //start generating images

    // Clear the colorbuffer and build background

    do {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set frame time for camera control
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        move();

        //Update viewMatrix for all
        cameraMatrix = Camera::Get().GetCameraMatrix();
        Model::viewMatrix = cameraMatrix;
        Light::Get().viewMatrix = cameraMatrix;

        floor.Draw();
        ceiling.Draw();

        if (start) {
                animation();
        }

        for (int i = 0; i < 4; i++) walls[i]->Draw();
        for (int i = 0; i < 3; i++) object[i]->Draw();

        Light::Get().Draw();

        glfwSwapBuffers(window);

        //Until user press escape or close the window, the program should loop.
    } while (!glfwWindowShouldClose(window));
    glfwTerminate();
    return 0;
}



