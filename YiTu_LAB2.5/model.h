//
// Created by Yi Tu on 2018/2/6.
//
#include <vector>
#include "math.h"
#include <iostream>
#include <string>
#include "texture.h"

#ifndef __GWU_MODEL__
#define __GWU_MODEL__


GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0f, 0.0f, 0.0f },
                        { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f },
                        { 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f } };
//================================
// ModelFace
//================================
class ModelFace {
public :
    std::vector< int > indices;

public :
    ModelFace() {
    }

    ~ModelFace() {
    }
};

//================================
// Model
//================================
class Model {
public :
    std::vector< vec3 > verts;
    std::vector< ModelFace > faces;

public :
    Model() {
    }

    ~Model() {
    }

    //=============================================
    // Load Model
    //=============================================
    void Free( void ) {
        verts.clear();
        faces.clear();
    }

    bool LoadModel( const char *path ) {
        if ( !path ) {
            return false;
        }

        Free();

        // open file
        FILE *fp = fopen( path, "r" );
        if ( !fp ) {
            return false;
        }

        unsigned int numVerts = 0;
        unsigned int numFaces = 0;
        // num of vertices and indices
        fscanf( fp, "data%d%d", &numVerts, &numFaces );

        // alloc vertex and index buffer
        verts.resize( numVerts );
        faces.resize( numFaces );

        // read vertices
        for ( unsigned int i = 0; i < numVerts; i++ ) {
            fscanf( fp, "%f%f%f", &verts[ i ].x, &verts[ i ].y, &verts[ i ].z );
        }

        // read indices
        for ( unsigned int i = 0; i < numFaces; i++ ) {
            int numSides = 0;
            fscanf( fp, "%i", &numSides );
            faces[ i ].indices.resize( numSides );

            for ( unsigned int k = 0; k < faces[ i ].indices.size(); k++ ) {
                fscanf( fp, "%i", &faces[ i ].indices[ k ] );
            }
        }

        // close file
        fclose( fp );

        ResizeModel();

        return true;
    }

    //=============================================
    // Render Model
    //=============================================
    void DrawEdges2D( void ) {
        glBegin( GL_LINES );
        for ( unsigned int i = 0; i < faces.size(); i++ ) {
            for ( unsigned int k = 0; k < faces[ i ].indices.size(); k++ ) {
                int p0 = faces[ i ].indices[ k ];
                int p1 = faces[ i ].indices[ ( k + 1 ) % faces[ i ].indices.size() ];
                glVertex2fv( verts[ p0 ].ptr() );
                glVertex2fv( verts[ p1 ].ptr() );
            }
        }
        glEnd();
    }

    void DrawEdges( void ) {
        glBegin( GL_LINES );
        for ( unsigned int i = 0; i < faces.size(); i++ ) {
            for ( unsigned int k = 0; k < faces[ i ].indices.size(); k++ ) {
                int p0 = faces[ i ].indices[ k ];
                int p1 = faces[ i ].indices[ ( k + 1 ) % faces[ i ].indices.size() ];
                glVertex3fv( verts[ p0 ].ptr() );
                glVertex3fv( verts[ p1 ].ptr() );
            }
        }
        glEnd();
    }



    void Draw( void ) {
        string filename = "/Users/niklaus/Desktop/graphics/resources/brick_texture.jpg";
        GLuint texture;
        const char* file = filename.c_str();
        texture = LoadTexture(file);
        glBindTexture(GL_TEXTURE_2D, texture);

        for ( unsigned int i = 0; i < faces.size(); i++ ) {
            //glColor4f( (rand()%100)/100, (rand()%100)/100, (rand()%100)/100, 1.0f);
            //glColor3f((rand()%255)/255, (rand()%255)/255, (rand()%255)/255);
            //glBegin( GL_POLYGON );
            glBegin( GL_LINES );

            for ( unsigned int k = 0; k < faces[ i ].indices.size(); k++ ) {
                int p0 = faces[ i ].indices[ k ];
                int p1 = faces[ i ].indices[ ( k + 1 ) % faces[ i ].indices.size() ];

                //glColor3fv(colors[rand()%8]);
                glNormal3fv( verts[ p0 ].ptr() );
                glTexCoord2f(0,0);
                glVertex3fv( verts[ p0 ].ptr() );


                glNormal3fv( verts[ p1 ].ptr() );
                glTexCoord2f(1,1);
                glVertex3fv( verts[ p1 ].ptr() );

            }
            glEnd();
        }
    }


    //=============================================
    // Resize Model
    //=============================================
    // scale the model into the range of [ -0.9, 0.9 ]
    void ResizeModel( void ) {
        // bound
        vec3 min, max;
        if ( !CalcBound( min, max ) ) {
            return;
        }

        // max side
        vec3 size = max - min;

        float r = size.x;
        if ( size.y > r ) {
            r = size.y;
        }
        if ( size.z > r ) {
            r = size.z;
        }

        if ( r < 1e-6f ) {
            r = 0;
        } else {
            r = 1.0f / r;
        }

        // scale
        for ( unsigned int i = 0; i < verts.size(); i++ ) {
            // [0, 1]
            verts[ i ] = ( verts[ i ] - min ) * r;

            // [-1, 1]
            verts[ i ] = verts[ i ] * 2.0f - vec3( 1.0f, 1.0f, 1.0f );

            // [-0.9, 0.9]
            verts[ i ] *= 0.9;
        }
    }

    bool CalcBound( vec3 &min, vec3 &max ) {
        if ( verts.size() <= 0 ) {
            return false;
        }

        min = verts[ 0 ];
        max = verts[ 0 ];

        for ( unsigned int i = 1; i < verts.size(); i++ ) {
            vec3 v = verts[ i ];

            if ( v.x < min.x ) {
                min.x = v.x;
            } else if ( v.x > max.x ) {
                max.x = v.x;
            }

            if ( v.y < min.y ) {
                min.y = v.y;
            } else if ( v.y > max.y ) {
                max.y = v.y;
            }

            if ( v.z < min.z ) {
                min.z = v.z;
            } else if ( v.z > max.z ) {
                max.z = v.z;
            }
        }

        return true;
    }

    //=============================================
    // Transform Model
    //=============================================
    // scale model
    void Scale( float r ) {
        for ( unsigned int i = 0; i < verts.size(); i++ ) {
            verts[ i ] *= r;
        }
    }

    void Translate( const vec3 &offset ) {
        // translate ...
        Matrix t;

        t.matrix[0][0] = 1.0f; t.matrix[0][1] = 0.0f; t.matrix[0][2] = 0.0f; t.matrix[0][3] = offset.x;
        t.matrix[1][0] = 0.0f; t.matrix[1][1] = 1.0f; t.matrix[1][2] = 0.0f; t.matrix[1][3] = offset.y;
        t.matrix[2][0] = 0.0f; t.matrix[2][1] = 0.0f; t.matrix[2][2] = 1.0f; t.matrix[2][3] = offset.z;
        t.matrix[3][0] = 0.0f; t.matrix[3][1] = 0.0f; t.matrix[3][2] = 0.0f; t.matrix[3][3] = 1.0f;

        for ( unsigned int i = 0; i < verts.size(); i++ ) {
            verts[ i ] = verts[ i ] * t;
        }
    }

    void Rotate( float x, float y, float z ) {
        // rotate ...
        Matrix rx, ry, rz,r;

        x = ((x)* PI / 180.0f);
        y = ((y)* PI / 180.0f);
        z = ((z)* PI / 180.0f);

        rx.matrix[0][0] = 1.0f; rx.matrix[0][1] = 0.0f; rx.matrix[0][2] = 0.0f; rx.matrix[0][3] = 0.0f;
        rx.matrix[1][0] = 0.0f; rx.matrix[1][1] = cosf(x); rx.matrix[1][2] = -sinf(x); rx.matrix[1][3] = 0.0f;
        rx.matrix[2][0] = 0.0f; rx.matrix[2][1] = sinf(x); rx.matrix[2][2] = cosf(x); rx.matrix[2][3] = 0.0f;
        rx.matrix[3][0] = 0.0f; rx.matrix[3][1] = 0.0f; rx.matrix[3][2] = 0.0f; rx.matrix[3][3] = 1.0f;

        ry.matrix[0][0] = cosf(y); ry.matrix[0][1] = 0.0f; ry.matrix[0][2] = -sinf(y); ry.matrix[0][3] = 0.0f;
        ry.matrix[1][0] = 0.0f; ry.matrix[1][1] = 1.0f; ry.matrix[1][2] = 0.0f; ry.matrix[1][3] = 0.0f;
        ry.matrix[2][0] = sinf(y); ry.matrix[2][1] = 0.0f; ry.matrix[2][2] = cosf(y); ry.matrix[2][3] = 0.0f;
        ry.matrix[3][0] = 0.0f; ry.matrix[3][1] = 0.0f; ry.matrix[3][2] = 0.0f; ry.matrix[3][3] = 1.0f;

        rz.matrix[0][0] = cosf(z); rz.matrix[0][1] = -sinf(z); rz.matrix[0][2] = 0.0f; rz.matrix[0][3] = 0.0f;
        rz.matrix[1][0] = sinf(z); rz.matrix[1][1] = cosf(z); rz.matrix[1][2] = 0.0f; rz.matrix[1][3] = 0.0f;
        rz.matrix[2][0] = 0.0f; rz.matrix[2][1] = 0.0f; rz.matrix[2][2] = 1.0f; rz.matrix[2][3] = 0.0f;
        rz.matrix[3][0] = 0.0f; rz.matrix[3][1] = 0.0f; rz.matrix[3][2] = 0.0f; rz.matrix[3][3] = 1.0f;

        r = rz * ry * rx;

        for ( unsigned int i = 0; i < verts.size(); i++ ) {
            verts[ i ] = verts[ i ] * r;
        }
    }
};

#endif // __GWU_MODEL__


