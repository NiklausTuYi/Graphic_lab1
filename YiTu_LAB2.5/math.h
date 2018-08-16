//
// Created by Yi Tu on 2018/2/7.
//
#include <math.h>
#include <assert.h>
#include <stdio.h>
#ifndef __GWU_VEC__
#define __GWU_VEC__


const float PI = 3.1415926f;


//matrix
class Matrix {
public:
    float matrix[4][4];
public:
    Matrix(){};
    ~Matrix(){};

    void init() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == j) {
                    matrix[i][j] = 1.0;
                } else
                    matrix[i][j] = 0.0;
            }
        }
    };
    void Rotate(float x, float y, float z)
    {
        Matrix rx, ry, rz;


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

        *this = rz * ry * rx;
    };

    void Scale(float x, float y, float z){
        Matrix s;

        s.matrix[0][0] = x; s.matrix[0][1] = 0.0f;   s.matrix[0][2] = 0.0f;   s.matrix[0][3] = 0.0f;
        s.matrix[1][0] = 0.0f;   s.matrix[1][1] = y; s.matrix[1][2] = 0.0f;   s.matrix[1][3] = 0.0f;
        s.matrix[2][0] = 0.0f;   s.matrix[2][1] = 0.0f;   s.matrix[2][2] = z; s.matrix[2][3] = 0.0f;
        s.matrix[3][0] = 0.0f;   s.matrix[3][1] = 0.0f;   s.matrix[3][2] = 0.0f;   s.matrix[3][3] = 1.0f;

        *this = s;
    };
    void Translate(float x, float y, float z){
        Matrix t;

        t.matrix[0][0] = 1.0f; t.matrix[0][1] = 0.0f; t.matrix[0][2] = 0.0f; t.matrix[0][3] = x;
        t.matrix[1][0] = 0.0f; t.matrix[1][1] = 1.0f; t.matrix[1][2] = 0.0f; t.matrix[1][3] = y;
        t.matrix[2][0] = 0.0f; t.matrix[2][1] = 0.0f; t.matrix[2][2] = 1.0f; t.matrix[2][3] = z;
        t.matrix[3][0] = 0.0f; t.matrix[3][1] = 0.0f; t.matrix[3][2] = 0.0f; t.matrix[3][3] = 1.0f;

        *this = t;
    };
    void printMatrix(){
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                printf("%f ", matrix[i][j]);
            }
            printf("\n");
        }
    };

    Matrix operator*(Matrix& r){
        Matrix tmp;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp.matrix[i][j] = matrix[i][0] * r.matrix[0][j]
                                   + matrix[i][1] * r.matrix[1][j]
                                   + matrix[i][2] * r.matrix[2][j]
                                   + matrix[i][3] * r.matrix[3][j];
            }
        }

        return tmp;
    };

};

//================================
// vec3
//================================
class vec3 {
public :
    float x, y, z;

public :
    vec3();
    vec3( float x, float y, float z );

    vec3 &			set( float x, float y, float z );

    vec3 &			zero( void );

    vec3			operator- ( void ) const;
    vec3			operator+ ( void ) const;

    vec3			operator+ ( const vec3 &v ) const;
    vec3			operator- ( const vec3 &v ) const;
    vec3			operator* ( float scalar ) const;
    vec3			operator* ( Matrix &m);
    vec3			operator/ ( float scalar ) const;

    vec3 &			operator= ( const vec3 &v );
    vec3 &			operator+=( const vec3 &v );
    vec3 &			operator-=( const vec3 &v );
    vec3 &			operator*=( float scalar );
    vec3 &			operator/=( float scalar );

    float &			operator[]( int index );
    const float &	operator[]( int index ) const;

    float			dot( const vec3 &v ) const;

    float			magnitude( void ) const;
    vec3 &			normalize( void );

    float *			ptr( void );
    const float *	ptr( void ) const;

public :
    friend vec3		operator*( float scalar, const vec3 &v );
};

vec3::vec3() {
    x = y = z = 0;
}

vec3::vec3( float x, float y, float z ) {
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3 &vec3::set( float x, float y, float z ) {
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
}

vec3 &vec3::zero( void ) {
    x = y = z = 0;

    return *this;
}

vec3 vec3::operator-( void ) const {
    return vec3( -x, -y, -z );
}

vec3 vec3::operator+( void ) const {
    return vec3( x, y, z );
}

vec3 vec3::operator+( const vec3 &v ) const {
    return vec3( x + v.x, y + v.y, z + v.z );
}

vec3 vec3::operator-( const vec3 &v ) const {
    return vec3( x - v.x, y - v.y, z - v.z );
}

vec3 vec3::operator*( float scalar ) const {
    return vec3( x * scalar, y * scalar, z * scalar );
}

vec3 vec3::operator*(Matrix &m) {

    float b[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    for (int i = 0; i < 4; i++) {

        b[i] = x * m.matrix[i][0] + y * m.matrix[i][1] + z * m.matrix[i][2] + 1 * m.matrix[i][3];
    }

    float x = b[0] / b[3];
    float y = b[1] / b[3];
    float z = b[2] / b[3];

    return vec3(x, y, z);
}

vec3 vec3::operator/( float scalar ) const {
    float inv = 1.0f / scalar;
    return vec3( x * inv, y * inv, z * inv );
}

vec3 &vec3::operator=( const vec3 &v ) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vec3 &vec3::operator+=( const vec3 &v ) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3 &vec3::operator-=( const vec3 &v ) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3 &vec3::operator*=( float scalar ) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

vec3 &vec3::operator/=( float scalar ) {
    float inv = 1.0f / scalar;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

float &vec3::operator[]( int index ) {
    assert( index >= 0 && index < 3 );
    return (&x)[ index ];
}

const float &vec3::operator[]( int index ) const {
    assert( index >= 0 && index < 3 );
    return (&x)[ index ];
}

float vec3::dot( const vec3 &v ) const {
    return x * v.x + y * v.y + z * v.z;
}

float vec3::magnitude( void ) const {
    return sqrtf( x * x + y * y + z * z );
}

vec3 &vec3::normalize( void ) {
    float mag = sqrtf( x * x + y * y + z * z );

    if ( mag < 1e-6f ) {
        x = y = z = 0;
    } else {
        float inv = 1.0f / mag;

        x *= inv;
        y *= inv;
        z *= inv;
    }

    return *this;
}

float *vec3::ptr( void ) {
    return &x;
}

const float *vec3::ptr( void ) const {
    return &x;
}

vec3 operator*( float scalar, const vec3 &v ) {
    return vec3( v.x * scalar, v.y * scalar, v.z * scalar );
}

#endif // __GWU_VEC__

