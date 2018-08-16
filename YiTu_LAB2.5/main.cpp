#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "model.h"
#include <GLUT/glut.h>
#include "texture.h"
#include <cstdlib>
#include <ctime>
#include "drawWall.h"
using namespace std;

//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;

// frame index
int g_frameIndex = 0;

// XZ position of the camera
float x = 0.0f, y = 3.0f, z = 10.0f;

float angle = 0.0f;

// model
Model g_model,g_model2,g_model3;

//================================
// init
//================================
void init( void ) {

    // load model
    g_model.LoadModel("/Users/niklaus/Desktop/graphics/resources/cow.d2");

    g_model2.LoadModel("/Users/niklaus/Desktop/graphics/resources/car.d2");
    g_model2.Translate(vec3(-1,0,2));

    g_model3.LoadModel("/Users/niklaus/Desktop/graphics/resources/walls.d");
    g_model3.Scale(6);
    g_model3.Translate(vec3(0,2,1));


//    GLfloat light_position[] = { -1.0, -1.0, 2.0, 0.0 };

}

//================================
// update
//================================
void update( void ) {
    // do something before rendering...
}

//================================
// render
//================================
void drawGrids( float height ) {
    float step = 0.1f;

    int n = 20;

    float r = step * n;

    glBegin( GL_LINES );

    for ( int i = -n; i <= n; i++ ) {
        glVertex3f( i * step, height, -r );
        glVertex3f( i * step, height, +r );
    }

    for ( int i = -n; i <= n; i++ ) {
        glVertex3f( -r, height, i * step );
        glVertex3f( +r, height, i * step );
    }

    glEnd();
}

void render( void ) {

    // clear color and depth buffer
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearDepth ( 1.0 );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // enable depth test
    glEnable( GL_DEPTH_TEST );
    glEnable (GL_TEXTURE_2D);
    // modelview matrix <------------------------------------------
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(
            x, y, z,
            x+ (sin(angle)), y-0.1, z-(cos(angle)),
            0.0f, 1.0f, 0.0f);

    srand (static_cast <unsigned> (time(0)));
    //srand(time(0));
    // draw grids
    glLineWidth( 1 );
    glColor4f( 0.2f, 0.2f, 0.5f, 1.0f );
    drawGrids( -0.9f );

    // draw model
    glLineWidth( 1 );
    glColor4f( 1.0, 0.0, 0.0, 1.0 );


    // render state
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT,GL_FILL);
    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // light source attributes
    GLfloat LightAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightPosition[] = { -1.0f, -1.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);



    glPushMatrix();
    // surface material attributes
    GLfloat material_Ka[] = { 0.250000f, 0.250000f, 0.250000f, 1.000000f };
    GLfloat material_Kd[] = { 0.400000f, 0.400000f, 0.400000f, 1.000000f };
    GLfloat material_Ks[] = { 0.774597f, 0.774597f, 0.774597f, 1.000000f };
    //GLfloat material_Ke[] = { 1, 1, 1, 1.0f };
    GLfloat material_Se = 10;
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    //glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT, GL_SHININESS, material_Se);
    g_model.Draw();
    glPopMatrix();


    GLfloat mat_ambient[] = { 0.250000f, 0.250000f, 0.250000f, 1.000000f };
    GLfloat mat_diffuse[] = { 0.400000f, 0.400000f, 0.400000f, 1.000000f };
    GLfloat mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.000000f };
    GLfloat mat_shininess[] = { 10 };

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    g_model2.Draw();
    glPopMatrix();

//    glPushMatrix();
//    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    g_model3.Draw();
//    glPopMatrix();

    // draw wall1
    filename ="/Users/niklaus/Desktop/graphics/resources/cement_brick_wall_texture.png";
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    polygon(0, 1, 2, 3);
    polygon(8, 9, 10, 11);
    polygon(12, 13, 14, 15);
    polygon(16, 17, 18, 19);
    glPopMatrix();

    // swap back and front buffers
    glutSwapBuffers();
}

//================================
// keyboard input
//================================
void key_press(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'p':
            break;
        case 'w':
            g_model.Translate(vec3(0,0,-0.5));
            glutPostRedisplay();
            break;
        case 's':
            g_model.Translate(vec3(0,0,+0.5));
            glutPostRedisplay();
            break;
        case 'a':
            g_model.Translate(vec3(-0.5,0,0));
            glutPostRedisplay();
            break;
        case 'd':
            g_model.Translate(vec3(0.5,0,0));
            glutPostRedisplay();
            break;
        case 'q':
            g_model.Rotate(0,0.5,0);
            glutPostRedisplay();
            break;
        case 'r':
            g_model.Rotate(0,-0.5,0);
            glutPostRedisplay();
            break;
        case '=':
            g_model.Scale(1.2f);
            glutPostRedisplay();
            break;
        case '-':
            g_model.Scale(0.8f);
            glutPostRedisplay();
            break;
        case ',':
            angle += 0.1;
            glutPostRedisplay();
            break;
        case '.':
            angle -= 0.1;
            glutPostRedisplay();
            break;
        case 'n':
            y -= 0.5;
            glutPostRedisplay();
            break;
        case 'm':
            y += 0.5;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void special_key(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT: //right arrow
            x += 0.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT: //left arrow
            x -= 0.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            z -= 0.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            z += 0.5;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

//================================
// reshape : update viewport and projection matrix when the window is resized
//================================
void reshape( int w, int h ) {
    // screen size
    g_screenWidth  = w;
    g_screenHeight = h;

    // viewport
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

    // projection matrix <------------------------------------------
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0f, (float)w / (float)h, 0.1f, 100.0f );
}


//================================
// timer : triggered every 16ms ( about 60 frames per second )
//================================
void timer( int value ) {
    // increase frame index
    g_frameIndex++;

    update();

    // render
    glutPostRedisplay();

    // reset timer
    glutTimerFunc( 16, timer, 0 );
}

//================================
// main
//================================
int main( int argc, char** argv ) {
    // create opengL window
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH );
    glutInitWindowSize( 600, 600 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "YiTu_Lab2" );


    // init
    init();

    // set callback functions
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key_press );
    glutSpecialFunc( special_key );
    glutTimerFunc( 16, timer, 0 );

    // main loop
    glutMainLoop();

    return 0;
}

