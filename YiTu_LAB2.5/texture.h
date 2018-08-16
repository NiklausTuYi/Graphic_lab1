//
// Created by Yi Tu on 2018/2/13.
//

#ifndef CG1_TEXTURE_H
#define CG1_TEXTURE_H
#include <math.h>
#include <stdio.h>
#include <vector>

// glut
#include <GLUT/GLUT.h>

// source
//#include <math/vec3.h>
//#include <model.h>

#include <string>
#include <iostream>
using namespace std;

GLuint LoadTexture(const char * filename)
{

    GLuint texture;

    int width, height;

    unsigned char * data;

    FILE * file;

    file = fopen(filename, "rb");

    if (file == NULL) { cout << "Wrong!!"; return 0; }
    width = 128;
    height = 128;
    data = (unsigned char *)malloc(width * height * 3);

    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }

    //define texture properties
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    return texture;
}

#endif //CG1_TEXTURE_H
