//
// Created by Yi Tu on 2018/2/13.
//

#ifndef CG1_DRAWWALL_H
#define CG1_DRAWWALL_H

#include "texture.h"
#include <string>
#include <iostream>

GLfloat vertices[][3] = {
        { -4.0, -1.0, -4.0 },{ 4.0, -1.0, -4.0 },{ 4.0, 4.0, -4.0 },{ -4.0, 4.0, -4.0 },
        { -4.0, -1.0, 4.0 },{ 4.0, -1.0, 4.0 },{ 4.0, -1.0, -4.0}, { -4.0, -1.0, -4.0 },
        {  4.0,  4.0, 4.0 },{ 4.0,  4.0, -4.0 },{ 4.0, -1.0, -4.0 },{ 4.0, -1.0,  4.0 },
        { -4.0,  4.0, 4.0 },{ 4.0,  4.0,  4.0 },{ 4.0, -1.0, 4.0 },{ -4.0, -1.0,  4.0 },
        { -4.0, 4.0, -4.0 },{ -4.0, 4.0, 4.0 },{ -4.0, -1.0, 4.0 },{ -4.0, -1.0, -4.0 },
        { -4.0, 4.0, -4.0 },{ 4.0, 4.0, -4.0 },{ 4.0, 4.0, -4.0 },{ -4.0, 4.0, -4.0 }
};

string filename;

void polygon(int a, int b, int c, int d)
{
    GLuint texture;
    const char* file = filename.c_str();
    texture = LoadTexture(file);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_POLYGON);
    //v means the parameter is a  array.

    glNormal3fv(vertices[a]);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(vertices[a]);

    glTranslatef(1.0, 0.0, 0.0);
    glNormal3fv(vertices[b]);
    glTexCoord2f(1.0, 0.0);
    glVertex3fv(vertices[b]);


    glNormal3fv(vertices[c]);
    glTexCoord2f(1.0, 1.0);
    glVertex3fv(vertices[c]);


    glNormal3fv(vertices[d]);
    glTexCoord2f(0.0, 1.0);
    glVertex3fv(vertices[d]);
    glEnd();
}

#endif //CG1_DRAWWALL_H
