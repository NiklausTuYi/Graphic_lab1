#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "Camera.h"
using namespace std;

class Light {
public:
    int numberLights;
    glm::vec3 * initialPosition;
    glm::vec3 * position;
    glm::vec3 * color;

    //singleton function declaration
    static Light & Get(){
        static Light mainLight = Light();
        return mainLight;
    }

    static void add(glm::vec3 position, glm::vec3 color){
        Get().initialPosition[Get().numberLights] = position;
        Get().position[Get().numberLights] = position;
        Get().color[Get().numberLights] = color;
        Get().numberLights += 1;
    }

    void Draw(){
        shader->Use();
        glBindVertexArray(VAO);
        glm::mat4 modelTrans;
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(Camera::Get().camera_mat));
        for (int i = 0; i < numberLights; i++) {
            modelTrans = glm::translate(glm::mat4(), Get().position[i]);
            glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(modelTrans));
            glUniform3f(glGetUniformLocation(shader->Program, "lightColor"), Get().color[i].x, Get().color[i].y, Get().color[i].z);
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }

private:
    Shader * shader;
    GLuint VBO, VAO, EBO;


    Light(){
        GLfloat vertices[] = {
                -2.0f,  -1.5f, 2.0f,
                2.0f, -1.5f, 2.0f,
                2.0f, -1.5f, -2.0f,
                -2.0f, -2.0f, -2.0f,
                0.0f,  1.5f, 0.0f
        };
        GLuint indices[] = {  // Note that we start from 0!
                0, 2, 1,
                0, 3, 2,
                0, 1, 4,
                1, 2, 4,
                2, 3, 4,
                3, 0, 4
        };

        numberLights = 0;
        initialPosition = new glm::vec3[10];
        position = new glm::vec3[10];
        color = new glm::vec3[10];
        shader = new Shader((char*)"/Users/niklaus/CLionProjects/CG1_Assign4/shaders/light.vert", (char*)"/Users/niklaus/CLionProjects/CG1_Assign4/shaders/light.frag");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
};
