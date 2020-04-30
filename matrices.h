#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#include "stdio.h"
#include "vector3f.h"

class matrix4x4{
public:
    float m[4][4];

public:

matrix4x4(){}
~matrix4x4(){}

void init_identity(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            m[i][j] = (j == i) ? 1 : 0;
        }
    }
printf("\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",m[0][0],m[0][1],m[0][2],m[0][3],m[1][0],m[1][1],m[1][2],m[1][3],m[2][0],m[2][1],m[2][2],m[2][3],m[3][0],m[3][1],m[3][2],m[3][3]);
}

matrix4x4 init_translation(float x, float y, float z){

    m[0][0] = 1;    m[0][1] = 0;    m[0][2] = 0;    m[0][3] = x;
    m[1][0] = 0;    m[1][1] = 1;    m[1][2] = 0;    m[1][3] = y;
    m[2][0] = 0;    m[2][1] = 0;    m[2][2] = 1;    m[2][3] = z;
    m[3][0] = 0;    m[3][1] = 0;    m[3][2] = 0;    m[3][3] = 1;

    return (*this);
}

matrix4x4 init_rotation(float x, float y, float z){

    matrix4x4 rx;
    matrix4x4 ry;
    matrix4x4 rz;

    x = x * 3.1415f/180.0f;
    y = y * 3.1415f/180.0f;
    z = z * 3.1415f/180.0f;

    rz.m[0][0] = cos(z);    rz.m[0][1] = -sin(z);   rz.m[0][2] = 0;          rz.m[0][3] = 0;
    rz.m[1][0] = sin(z);    rz.m[1][1] = cos(z);    rz.m[1][2] = 0;          rz.m[1][3] = 0;
    rz.m[2][0] = 0;         rz.m[2][1] = 0;         rz.m[2][2] = 1;          rz.m[2][3] = 0;
    rz.m[3][0] = 0;         rz.m[3][1] = 0;         rz.m[3][2] = 0;          rz.m[3][3] = 1;

    rx.m[0][0] = 1;         rx.m[0][1] = 0;         rx.m[0][2] = 0;          rx.m[0][3] = 0;
    rx.m[1][0] = 0;         rx.m[1][1] = cos(x);    rx.m[1][2] = -sin(x);    rx.m[1][3] = 0;
    rx.m[2][0] = 0;         rx.m[2][1] = sin(x);    rx.m[2][2] = cos(x);     rx.m[2][3] = 0;
    rx.m[3][0] = 0;         rx.m[3][1] = 0;         rx.m[3][2] = 0;          rx.m[3][3] = 1;

    ry.m[0][0] = cos(y);    ry.m[0][1] = 0;         ry.m[0][2] = -sin(y);    ry.m[0][3] = 0;
    ry.m[1][0] = 0;         ry.m[1][1] = 1;         ry.m[1][2] = 0;          ry.m[1][3] = 0;
    ry.m[2][0] = sin(y);    ry.m[2][1] = 0;         ry.m[2][2] = cos(y);     ry.m[2][3] = 0;
    ry.m[3][0] = 0;         ry.m[3][1] = 0;         ry.m[3][2] = 0;          ry.m[3][3] = 1;

    return rx.mult(ry.mult(rz));
}

matrix4x4 init_scale(float x, float y, float z){

    m[0][0] = x;    m[0][1] = 0;    m[0][2] = 0;    m[0][3] = 0;
    m[1][0] = 0;    m[1][1] = y;    m[1][2] = 0;    m[1][3] = 0;
    m[2][0] = 0;    m[2][1] = 0;    m[2][2] = z;    m[2][3] = 0;
    m[3][0] = 0;    m[3][1] = 0;    m[3][2] = 0;    m[3][3] = 1;

    return (*this);
}

matrix4x4 init_camera(vector3f forward, vector3f up){

    vector3f f = forward;
    f.normalized();

    vector3f r = up;
    r = r.cross(f);

    vector3f u = f.cross(r);

    m[0][0] = r.x;    m[0][1] = r.y;    m[0][2] = r.z;    m[0][3] = 0;
    m[1][0] = u.x;    m[1][1] = u.y;    m[1][2] = u.z;    m[1][3] = 0;
    m[2][0] = f.x;    m[2][1] = f.y;    m[2][2] = f.z;    m[2][3] = 0;
    m[3][0] = 0;      m[3][1] = 0;      m[3][2] = 0;      m[3][3] = 1;

    return (*this);
}

matrix4x4 init_perspective_projection(float fov, float height, float width, float znear, float zfar){

    float aspect_ratio = width/height;
    float radian_fov = fov * 3.1415f/180;

    float halftanfov = tan(radian_fov/2);

    float zrange = znear - zfar;

    m[0][0] = 1.0f/(halftanfov * aspect_ratio);    m[0][1] = 0;                  m[0][2] = 0;                         m[0][3] = 0;
    m[1][0] = 0;                                   m[1][1] = 1.0f/halftanfov;    m[1][2] = 0;                         m[1][3] = 0;
    m[2][0] = 0;                                   m[2][1] = 0;                  m[2][2] = (-znear - zfar)/zrange;    m[2][3] = 2 * zfar * znear/zrange;
    m[3][0] = 0;                                   m[3][1] = 0;                  m[3][2] = 1;                         m[3][3] = 0;

    return (*this);
}

void sett(int x, int y, float value){
    m[x][y] = value;
}

float get(int x, int y){
    return m[x][y];
}

matrix4x4 mult(matrix4x4 r){
    matrix4x4 res;

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
           res.sett(i,j,m[i][0] * r.get(0,j) +
                        m[i][1] * r.get(1,j) +
                        m[i][2] * r.get(2,j) +
                        m[i][3] * r.get(3,j));
        }

    }

    return res;
}

};

#endif // MATRICES_H_INCLUDED
