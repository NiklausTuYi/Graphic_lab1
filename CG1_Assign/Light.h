//
// Created by Yi Tu on 2018/2/26.
//

#ifndef CG1_ASSIGN1_LIGHT_H
#define CG1_ASSIGN1_LIGHT_H
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
    glm::mat4 viewMatrix;

    static Light & Get(){
        static Light light = Light();
        return light;
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
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glm::mat4 trans;
        for (int i = 0; i < numberLights; i++) {
            trans = glm::translate(glm::mat4(), Get().position[i]);
            glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniform3f(glGetUniformLocation(shader->Program, "lightColor"), Get().color[i].x, Get().color[i].y, Get().color[i].z);
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }

private:
    Shader * shader;
    GLuint VBO, VAO, EBO;

    Light() {

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

//        GLfloat vertices[] = {
//                -5.53777e-08f,            1.0f,  2.87212e-08f,
//                0.705667f,     0.712466f,  2.87212e-08f,
//                1.0f, -0.000909919f,  2.87212e-08f,
//                0.71298f,    -0.707007f,  2.87212e-08f,
//                -5.53777e-08f,           -1.0f,  2.87212e-08f,
//                0.570897f,     0.712466f,     0.436126f,
//                0.809017f, -0.000909919f,     0.618034f,
//                0.576813f,    -0.707007f,     0.440646f,
//                0.218063f,     0.712466f,     0.705667f,
//                0.309017f, -0.000909919f,            1.0f,
//                0.220323f,    -0.707007f,      0.71298f,
//                -0.218063f,     0.712466f,     0.705667f,
//                -0.309017f, -0.000909919f,            1.0f.
//                -0.220323f,    -0.707007f,      0.71298f,
//                -0.570897f,     0.712466f,     0.436126f,
//                -0.809017f, -0.000909919f,     0.618034f,
//                -0.576813f,    -0.707007f,     0.440646f,
//                -0.705668f,     0.712466f,  -3.6145e-08f,
//                -1.0f, -0.000909919f, -6.32006e-08f,
//                -0.71298f,    -0.707007f, -3.68172e-08f,
//                -0.570897f,     0.712466f,    -0.436126f,
//                -0.809017f, -0.000909919f,    -0.618034f,
//                -0.576813f,    -0.707007f,    -0.440646f,
//                -0.218063f,     0.712466f,    -0.705667f,
//                -0.309017f, -0.000909919f,           -1.0f,
//                -0.220323f,    -0.707007f,     -0.71298f,
//                0.218064f,     0.712466f,    -0.705667f,
//                0.309018f, -0.000909919f,           -1.0f,
//                0.220323f,    -0.707007f,     -0.71298f,
//                0.570897f,     0.712466f,    -0.436126f,
//                0.809018f, -0.000909919f,    -0.618033f,
//                0.576813f,    -0.707007f,    -0.440645f,
//        };
//        GLuint indices[] = {  // Note that we start from 0!
//                	     1,     2,     6,
//                	     2,     3,     7,     6,
//                	     3,     4,     8,     7,
//                	     4,     5,     8,
//                	     1,     6,     9,
//                	     6,     7,    10,     9,
//                	     7,     8,    11,   10,
//                	     8,     5,    11,
//                	     1,     9,    12,
//                	     9,    10,    13,    12,
//                	    10,    11,    14,    13,
//                	    11,     5,    14,
//                	     1,    12,    15,
//                	    12,    13,    16,    15,
//                	    13,    14,    17,    16,
//                	    14,     5,    17,
//                	     1,    15,    18,
//                	    15,    16,    19,    18,
//                	    16,    17,    20,    19,
//                	    17,     5,    20,
//                	     1,    18,    21,
//                	    18,    19,    22,    21,
//                	    19,    20,    23,    22,
//                	    20,     5,    23,
//                	     1,    21,    24,
//                	    21,    22,    25,    24,
//                	    22,    23,    26,    25,
//                	    23,     5,    26,
//                	     1,    24,    27,
//                	    24,    25,    28,    27,
//                	    25,    26,    29,    28,
//                	    26,     5,    29,
//                	     1,    27,    30,
//                	    27,    28,    31,    30,
//                	    28,    29,    32,    31,
//                	    29,     5,    32,
//                	     1,    30,     2,
//                	    30,    31,     3,     2,
//                	    31,    32,     4,     3,
//                	    32,     5,     4,
//        };

        numberLights = 0;
        initialPosition = new glm::vec3[10];
        position = new glm::vec3[10];
        color = new glm::vec3[10];

        shader = new Shader((char *)"/Users/niklaus/CLionProjects/CG1_Assign/shaders/light.vert", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/shaders/light.frag");

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

#endif //CG1_ASSIGN1_LIGHT_H
