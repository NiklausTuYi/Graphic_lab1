//standard include
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//OpenGL include
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Model.h"
using namespace std;

//setting
const GLuint screenWidth = 800, screenHeight = 600;
glm::vec3 eye = glm::vec3(0.0f, 10.0f, 20.0f);
bool keys[1024] = { false };
GLfloat deltaTime = 0.0f;
GLfloat last = 0.0f;
GLfloat current = 0.0f;

Model * object[3];

void init(){
    Camera::Get().set(eye, screenWidth, screenHeight);

    Light::add(glm::vec3(10.0, 30, 10.0), glm::vec3(1.0, 1.0, 1.0));
    Light::add(glm::vec3(30.0, 30, -30.0), glm::vec3(1.0, 1.0, 1.0));
    Light::add(glm::vec3(-5.0, 30, 10.0), glm::vec3(1.0, 1.0, 1.0));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    //update key pressing
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

//void animation(){
//    object[0]->position = object[0]->position + glm::vec3( glm::sin((glfwGetTime() - startTime)*3),0.0f, 0.0f);
//    object[1]->position = object[1]->position + glm::vec3( 0.0f, 0.1 * glm::cos(glfwGetTime() - startTime)*3,0.0f);
//    object[2]->position = object[2]->position + glm::vec3( 0.5 * glm::sin((glfwGetTime() - startTime)*3),0.0f, 0.2 * glm::cos(glfwGetTime() - startTime)*3);
//}

void move()
{
    //  controls
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


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "YiTu_Lab4", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, 1600, 1200);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);

    init();

    //model
    Model floor((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/ground.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/brickpic.png",true);
    Model * walls[4];
    walls[0] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/bricks.png",true);
    walls[0]->position = glm::vec3(0.0f, 0.0f, -40.0f);
    walls[0]->scaleDegree = glm::vec3(1.0f, 4.0f, 1.0f);

    walls[1] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/bricks.png",true);
    walls[1]->position = glm::vec3(0.0f, 0.0f, 40.0f);
    walls[1]->scaleDegree = glm::vec3(1.0f, 4.0f, 1.0f);

    walls[2] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/bricks.png",true);
    walls[2]->position =glm::vec3(40.0f, 0.0f, 0.0f);
    walls[2]->rotationDegree = 90.0f;
    walls[2]->scaleDegree = glm::vec3(1.0f, 4.0f, 1.0f);

    walls[3] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/wall.d2", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/bricks.png",true);
    walls[3]->position = glm::vec3(-40.0f, 0.0f, 0.0f);
    walls[3]->rotationDegree = -90.0f;
    walls[3]->scaleDegree = glm::vec3(1.0f, 4.0f, 1.0f);

    object[0] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/cow.d", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/solidcolor2.png", false, constant);
    object[0]->rotationDegree = -90.0f;
    object[0]->position = glm::vec3(0.0f, 7.6f, 0.0f);
    object[0]->scaleDegree = glm::vec3(2.0f, 2.0f, 2.0f);

    object[1] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/cow.d", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/solidcolor2.png", false, gouraud);
    object[1]->position = glm::vec3(8.0f, 7.6f, 0.0f);
    object[1]->rotationDegree = -90.0f;
    object[1]->shininess = 0.5f;
    object[1]->scaleDegree = glm::vec3(2.0f, 2.0f, 2.0f);

    object[2] = new Model((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/cow.d", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/data/solidcolor2.png", false, phong);
    object[2]->position = glm::vec3(-8.0f, 7.6f, 0.0f);
    object[2]->rotationDegree = -90.0f;
    object[2]->shininess = 0.5f;
    object[2]->scaleDegree = glm::vec3(2.0f, 2.0f, 2.0f);

    //start generating images
    do {
        // Set frame time for camera control
        GLfloat current = glfwGetTime();
        deltaTime = current - last;
        last = current;

        // Check and call events for user input control
        glfwPollEvents();
        move();

        // Clear the colorbuffer and build background
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Update cameraMatrix for all
        Camera::Get().GetMatrix();

        floor.Draw();

        for (int i = 0; i < 4; i++) walls[i]->Draw();

        object[0]->Draw();
        object[1]->Draw();
        object[2]->Draw();
        //cow.Draw();

        Light::Get().Draw();
        // Swap the buffers
        glfwSwapBuffers(window);
    } while (!glfwWindowShouldClose(window));
    glfwTerminate();
    return 0;
}




