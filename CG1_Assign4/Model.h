#pragma once
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


enum Shading {
    gouraud,
    phong,
    constant,
};

class Model {
public:

    glm::vec3 position, rotationAxle, scaleDegree;
    GLfloat rotationDegree;
    bool texCoordIncluded = false;
    int stride;

    int numberPoints, numberPolygons;
    GLfloat * vertices;
    GLuint * polygons;
    enum Shading shadingMethod;
    GLfloat * fvertex;

    ifstream dataFile;
    glm::mat4 trans;
    Shader * shader;
    GLuint texture;
    GLfloat shininess;
    GLchar * texPath;
    //graphics properties
    GLuint VBO, VAO, EBO;

    Model(GLchar * path, GLchar * texPath, bool texCoordsIncluded, enum Shading shadingMethod=phong) {
        this->shadingMethod = shadingMethod;
        if (this->shadingMethod == constant) {
            this->position = position;
            this->rotationDegree = rotationDegree;
            this->rotationAxle = glm::vec3(0.0f, 1.0f, 0.0f);
            this->shininess = shininess;
            this->texPath = texPath;
            stride = 8;
            string tmpStr;
            GLint tmpInt;
            stringstream oneLine;
            dataFile.open(path, ios::in);
            if (!dataFile.is_open()) {
                cout << "error, data file is not open!" << endl;
            }
            getline(dataFile, tmpStr);
            oneLine.str(tmpStr);
            oneLine >> tmpStr >> numberPoints >> numberPolygons;

            vertices = new GLfloat[numberPoints * 5];
            polygons = new GLuint[numberPolygons * 3];
            //load point coordinates
            for (int i = 0; i < numberPoints; i++) {
                oneLine.clear();
                getline(dataFile, tmpStr);
                oneLine.str(tmpStr);
                oneLine >> vertices[i * 5] >> vertices[i * 5 + 1] >> vertices[i * 5 + 2];
            }
            //load polygons' points indices
            for (int i = 0; i < numberPolygons; i++) {
                oneLine.clear();
                getline(dataFile, tmpStr);
                oneLine.str(tmpStr);
                oneLine >> tmpInt >> polygons[i * 3] >> polygons[i * 3 + 1] >> polygons[i * 3 + 2];
            }
            //load tex coordinates
            if (texCoordsIncluded) {
                for (int i = 0; i < numberPoints; i++) {
                    oneLine.clear();
                    getline(dataFile, tmpStr);
                    oneLine.str(tmpStr);
                    oneLine >> tmpInt >> vertices[i * 5 + 3] >> vertices[i * 5 + 4];
                }
            }
            else {
                for (int i = 0; i < numberPoints; i++) {
                    vertices[i * 5 + 3] = (GLfloat)((rand() % 100000)) / 100000;
                    vertices[i * 5 + 4] = (GLfloat)((rand() % 100000)) / 100000;
                }
            }
            ComputeNormalByPolygon();
            //setup shader
            shader = new Shader((char *)"/Users/niklaus/CLionProjects/CG1_Assign4/shaders/constant_shader.vert", (char *)"/Users/niklaus/CLionProjects/CG1_Assign4/shaders/constant_shader.frag");


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


            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            //buffer vertices data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numberPolygons*3*stride, &fvertex[0], GL_STATIC_DRAW);
            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // Normal attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            // Tex coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glBindVertexArray(0); // Unbind VAO
            //write shininess to uniform
            shader->Use();
            glUniform1f(glGetUniformLocation(shader->Program, "shininess"), this->shininess);
        }
        else {
            this->position = glm::vec3(0.0f, 0.0f, 0.0f);
            this->scaleDegree = glm::vec3(1.0f, 1.0f, 1.0f);
            this->rotationDegree = 0.0f;
            this->rotationAxle = glm::vec3(0.0f, 1.0f, 0.0f);
            this->shininess = 0.5f;
            this->texPath = texPath;


            stride = 8;
            string tmpStr;
            GLint tmpInt;
            stringstream oneLine;
            dataFile.open(path, ios::in);
            if (!dataFile.is_open()) {
                cout << "error, data file is not open!" << endl;
            }
            getline(dataFile, tmpStr);
            oneLine.str(tmpStr);
            oneLine >> tmpStr >> numberPoints >> numberPolygons;
            //cout << "number of points: " << numberOfPoints << ".\n" << "number of polygons: " << numberOfPolygons << endl;
            vertices = new GLfloat[numberPoints * stride];
            polygons = new GLuint[numberPolygons * 3];
            //load point coordinates
            for (int i = 0; i < numberPoints; i++) {
                oneLine.clear();
                getline(dataFile, tmpStr);
                oneLine.str(tmpStr);
                oneLine >> vertices[i * stride] >> vertices[i * stride + 1] >> vertices[i * stride + 2];
            }
            //load polygons' points indices
            for (int i = 0; i < numberPolygons; i++) {
                oneLine.clear();
                getline(dataFile, tmpStr);
                oneLine.str(tmpStr);
                oneLine >> tmpInt >> polygons[i * 3] >> polygons[i * 3 + 1] >> polygons[i * 3 + 2];
            }
            //load tex coordinates
            if (texCoordsIncluded) {
                for (int i = 0; i < numberPoints; i++) {
                    oneLine.clear();
                    getline(dataFile, tmpStr);
                    oneLine.str(tmpStr);
                    oneLine >> tmpInt >> vertices[i * stride + 6] >> vertices[i * stride + 7];
                }
            }
            else {
                for (int i = 0; i < numberPoints; i++) {
                    vertices[i * stride + 6] = (GLfloat)((rand() % 100000)) / 100000;
                    vertices[i * stride + 7] = (GLfloat)((rand() % 100000)) / 100000;
                }
            }


            ComputeNormalByVertex();
            //setup shader
            if (shadingMethod == phong) {
                shader = new Shader((char *) "/Users/niklaus/CLionProjects/CG1_Assign4/shaders/phong_shader.vert",
                                    (char *) "/Users/niklaus/CLionProjects/CG1_Assign4/shaders/phong_shader.frag");
            } else if (shadingMethod == gouraud) {
                shader = new Shader((char *) "/Users/niklaus/CLionProjects/CG1_Assign4/shaders/gouraud_shader.vert",
                                    (char *) "/Users/niklaus/CLionProjects/CG1_Assign4/shaders/gouraud_shader.frag");
            }
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

            SOIL_free_image_data(image);
            glBindTexture(GL_TEXTURE_2D, 0);
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glBindVertexArray(VAO);
            //buffer vertices data
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*numberPoints*stride, &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numberPolygons * 3, &polygons[0], GL_STATIC_DRAW);
            // Position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            // Normal attribute
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
            // Tex coord attribute
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glBindVertexArray(0); // Unbind VAO
            //write shininess to uniform
            shader->Use();
            glUniform1f(glGetUniformLocation(shader->Program, "shininess"), this->shininess);
        }

    }



    void Draw(){
        shader->Use();
        glBindTexture(GL_TEXTURE_2D, texture);
        UpdateModelTrans();
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(Camera::Get().camera_mat));
        glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(trans));
        glUniform3f(glGetUniformLocation(shader->Program, "viewPos"), Camera::Get().eye.x, Camera::Get().eye.y, Camera::Get().eye.z);
        glUniform1i(glGetUniformLocation(shader->Program, "numberOfLights"), Light::Get().numberLights);
        glUniform3fv(glGetUniformLocation(shader->Program, "lightColor"), Light::Get().numberLights, glm::value_ptr(Light::Get().color[0]));
        glUniform3fv(glGetUniformLocation(shader->Program, "lightPos"), Light::Get().numberLights, glm::value_ptr(Light::Get().position[0]));

        glBindVertexArray(VAO);
        if(this->shadingMethod == constant){
            glDrawArrays(GL_TRIANGLES, 0, numberPolygons*3);
        } else{
            glDrawElements(GL_TRIANGLES, numberPolygons * 3, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }

    ~Model(){
        delete [] vertices;
        delete [] polygons;
        delete [] fvertex;
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void UpdateModelTrans(){
        trans = glm::translate(glm::mat4(), this->position);
        trans = glm::rotate(trans, glm::radians(rotationDegree), rotationAxle);
        trans = glm::scale(trans, glm::vec3(scaleDegree));
    }

    void ComputeNormalByVertex(){
        glm::vec3 * normalByVertex = new glm::vec3[numberPoints];
        int * numPolygonsForEachPoint = new int[numberPoints];
        for (int i = 0; i < numberPoints; i++) {
            numPolygonsForEachPoint[i] = 0;
        }
        glm::vec3 firstPoint, secondPoint, thirdPoint, v1, v2, currentNormal;
        for (int i = 0; i < numberPolygons; i++) {
            firstPoint = glm::vec3(vertices[polygons[i * 3 + 0]* stride + 0], vertices[polygons[i * 3 + 0]* stride + 1], vertices[polygons[i * 3 + 0]* stride + 2]);
            secondPoint = glm::vec3(vertices[polygons[i * 3 + 1] * stride + 0], vertices[polygons[i * 3 + 1] * stride + 1], vertices[polygons[i * 3 + 1]* stride + 2]);
            thirdPoint = glm::vec3(vertices[polygons[i * 3 + 2] * stride + 0], vertices[polygons[i * 3 + 2] * stride + 1], vertices[polygons[i * 3 + 2]* stride + 2]);
            v1 = secondPoint-firstPoint;
            v2 = thirdPoint-secondPoint;

            glm::vec3 crossVector;
            crossVector[0] = v1[1] * v2[2] - v1[2] * v2[1];
            crossVector[1] = v1[2] * v2[0] - v1[0] * v2[2];
            crossVector[2] = v1[0] * v2[1] - v1[1] * v2[0];

            currentNormal = glm::normalize(crossVector);

            for (int pointIndex = 0; pointIndex < 3; pointIndex++) {
                int currentPoint = polygons[i * 3 + pointIndex];
                normalByVertex[currentPoint] = normalByVertex[currentPoint] + currentNormal;
                numPolygonsForEachPoint[currentPoint]++;
            }
        }
        for (int i = 0; i < numberPoints; i++) {
            normalByVertex[i] = glm::normalize(normalByVertex[i] / ((GLfloat)numPolygonsForEachPoint[i]));
            vertices[i * stride + 3] = normalByVertex[i].x;
            vertices[i * stride + 4] = normalByVertex[i].y;
            vertices[i * stride + 5] = normalByVertex[i].z;
        }
        delete [] normalByVertex;
        delete [] numPolygonsForEachPoint;
    }

    void ComputeNormalByPolygon(){
        fvertex = new GLfloat[numberPolygons*3*stride];
        glm::vec3 normalByPolygon,p[3], v1, v2;
        for (int i = 0; i < numberPolygons; i++) {
            p[0] = glm::vec3(vertices[polygons[i * 3 + 0] * 5 + 0], vertices[polygons[i * 3 + 0] * 5 + 1], vertices[polygons[i * 3 + 0] * 5 + 2]);
            p[1] = glm::vec3(vertices[polygons[i * 3 + 1] * 5 + 0], vertices[polygons[i * 3 + 1] * 5 + 1], vertices[polygons[i * 3 + 1] * 5 + 2]);
            p[2] = glm::vec3(vertices[polygons[i * 3 + 2] * 5 + 0], vertices[polygons[i * 3 + 2] * 5 + 1], vertices[polygons[i * 3 + 2] * 5 + 2]);
            v1 = p[1] - p[0];
            v2 = p[2] - p[1];

            glm::vec3 crossVector;
            crossVector[0] = v1[1] * v2[2] - v1[2] * v2[1];
            crossVector[1] = v1[2] * v2[0] - v1[0] * v2[2];
            crossVector[2] = v1[0] * v2[1] - v1[1] * v2[0];

            normalByPolygon = glm::normalize(crossVector);
            for (int pIndex = 0; pIndex < 3; pIndex++) {
                //move point xyz
                fvertex[(i * 3 + pIndex) * stride + 0] = p[pIndex].x;
                fvertex[(i * 3 + pIndex) * stride + 1] = p[pIndex].y;
                fvertex[(i * 3 + pIndex) * stride + 2] = p[pIndex].z;
                //move point normal
                fvertex[(i * 3 + pIndex) * stride + 3] = normalByPolygon.x;
                fvertex[(i * 3 + pIndex) * stride + 4] = normalByPolygon.y;
                fvertex[(i * 3 + pIndex) * stride + 5] = normalByPolygon.z;
                //move point tex coordinates
                fvertex[(i * 3 + pIndex) * stride + 6] = vertices[polygons[i * 3 + pIndex] * 5 + 3];
                fvertex[(i * 3 + pIndex) * stride + 7] = vertices[polygons[i * 3 + pIndex] * 5 + 4];
            }
        }
    }
};
