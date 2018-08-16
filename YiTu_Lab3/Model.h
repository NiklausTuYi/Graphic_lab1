//
// Created by Yi Tu on 2018/2/6.
//#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include "Camera.h"
#include "Shader.h"
#include "Light.h"

using namespace std;


class Model {
public:
    //some variables
    ifstream file;

    Shader * shader;
    GLuint texture;
    GLfloat shininess;
    GLchar * texPath;
    //graphics properties
    GLuint VBO, VAO, EBO;


    //states
    glm::mat4 trans;
    glm::vec3 position, rotationAxles, scaleDegree;
    GLfloat rotationDegree;
    static glm::mat4 viewMatrix;
    bool texCoordIncluded = false;
    int stride = 8;

    GLfloat * vertices;
    GLuint * faces;
    int numberVertex, numberFaces;

    Model(GLchar * path, GLchar * texPath, bool texCoordsIncluded){

        this->scaleDegree = glm::vec3(1.0f, 1.0f, 1.0f);
        this->shininess = 0.0f;
        this->texPath = texPath;
        this->rotationAxles = glm::vec3(0.0f, 1.0f, 0.0f);

        string tmpStr;
        GLint tmpInt;
        stringstream Line;
        shader = new Shader((char *)"/Users/niklaus/CLionProjects/CG1_Assign/shaders/model_shader.vert", (char *)"/Users/niklaus/CLionProjects/CG1_Assign/shaders/model_shader.frag");

        file.open(path, ios::in);
        if (!file.is_open()) {
            cout << "error, data file is not open!" << endl;
        }
        getline(file, tmpStr);
        Line.str(tmpStr);
        Line >> tmpStr >> numberVertex >> numberFaces;
        //cout << "number of points: " << numberVertex << ".\n" << "number of faces: " << numberFaces << endl;
        vertices = new GLfloat[numberVertex * stride];
        faces = new GLuint[numberFaces * 3];
        //load point coordinates
        for (int i = 0; i < numberVertex; i++) {
            Line.clear();
            getline(file, tmpStr);
            Line.str(tmpStr);
            Line >> vertices[i * stride] >> vertices[i * stride + 1] >> vertices[i * stride + 2];
        }
        //load faces' points indices
        for (int i = 0; i < numberFaces; i++) {
            Line.clear();
            getline(file, tmpStr);
            Line.str(tmpStr);
            Line >> tmpInt >> faces[i * 3] >> faces[i * 3 + 1] >> faces[i * 3 + 2];
        }
        //load tex coordinates
        if (texCoordsIncluded) {
            for (int i = 0; i < numberVertex; i++) {
                Line.clear();
                getline(file, tmpStr);
                Line.str(tmpStr);
                Line >> tmpInt >> vertices[i * stride + 6] >> vertices[i * stride + 7];
            }
        }
        else {
            for (int i = 0; i < numberVertex; i++) {
                vertices[i * stride + 6] = (GLfloat)((rand() % 100000)) / 100000;
                vertices[i * stride + 7] = (GLfloat)((rand() % 100000)) / 100000;
            }
        }


        ComputeNormal();

        LoadTexture();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        //buffer vertices data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numberVertex*stride, &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numberFaces * 3, &faces[0], GL_STATIC_DRAW);
        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Tex coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glBindVertexArray(0);

        shader->Use();
        glUniform1f(glGetUniformLocation(shader->Program, "shininess"), this->shininess);
    }


    void Draw(){
        shader->Use();
        glBindTexture(GL_TEXTURE_2D, texture);
        UpdateModelTrans();
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), Camera::Get().eye.x, Camera::Get().eye.y, Camera::Get().eye.z);
        glUniform1i(glGetUniformLocation(shader->Program, "numberLights"), Light::Get().numberLights);
        glUniform3fv(glGetUniformLocation(shader->Program, "lightColor"), Light::Get().numberLights, glm::value_ptr(Light::Get().color[0]));
        glUniform3fv(glGetUniformLocation(shader->Program, "lightPos"), Light::Get().numberLights, glm::value_ptr(Light::Get().position[0]));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, numberFaces * 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void UpdateModelTrans(){
        trans = glm::translate(glm::mat4(), this->position);
        trans = glm::rotate(trans, glm::radians(rotationDegree), rotationAxles);
        trans = glm::scale(trans, glm::vec3(scaleDegree));
    }



    void LoadTexture(){
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Load image, create texture and generate mipmaps
        int width, height;
        unsigned char* image = SOIL_load_image(texPath, &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        /* for (int i = 0; i < width; i++) {
            for (int j = 0; j < width; j++) {
                cout << (int)image[j*width + i] << " ";
            }
            cout << endl;
        }*/
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glm::vec3 cross(glm::vec3 v1, glm::vec3 v2) {
        glm::vec3 returnVector;
        returnVector[0] = v1[1] * v2[2] - v1[2] * v2[1];
        returnVector[1] = v1[2] * v2[0] - v1[0] * v2[2];
        returnVector[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return returnVector;
    }

    void ComputeNormal(){
        glm::vec3 * vertexNormal = new glm::vec3[numberVertex];
        int * numFacesofEachPoint = new int[numberVertex];
        for (int i = 0; i < numberVertex; i++) {
            numFacesofEachPoint[i] = 0;
        }
        glm::vec3 p1, p2, p3, v1, v2, currentNormal;
        for (int i = 0; i < numberFaces; i++) {
            p1 = glm::vec3(vertices[faces[i * 3 + 0]* stride + 0], vertices[faces[i * 3 + 0]* stride + 1], vertices[faces[i * 3 + 0]* stride + 2]);
            p2 = glm::vec3(vertices[faces[i * 3 + 1] * stride + 0], vertices[faces[i * 3 + 1] * stride + 1], vertices[faces[i * 3 + 1]* stride + 2]);
            p3 = glm::vec3(vertices[faces[i * 3 + 2] * stride + 0], vertices[faces[i * 3 + 2] * stride + 1], vertices[faces[i * 3 + 2]* stride + 2]);
            v1 = p2-p1;
            v2 = p3-p2;
            currentNormal = glm::normalize(cross(v1, v2));

            for (int pointIndex = 0; pointIndex < 3; pointIndex++) {
                int currentPoint = faces[i * 3 + pointIndex];
                vertexNormal[currentPoint] = vertexNormal[currentPoint] + currentNormal;
                numFacesofEachPoint[currentPoint]++;
            }
        }
        for (int i = 0; i < numberVertex; i++) {
            vertexNormal[i] = glm::normalize(vertexNormal[i] / ((GLfloat)numFacesofEachPoint[i]));
            vertices[i * stride + 3] = vertexNormal[i].x;
            vertices[i * stride + 4] = vertexNormal[i].y;
            vertices[i * stride + 5] = vertexNormal[i].z;
        }
        delete [] vertexNormal;
        delete [] numFacesofEachPoint;
    }

    ~Model(){
        delete [] vertices;
        delete [] faces;
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};
