#ifndef VECTOR3F_H_INCLUDED
#define VECTOR3F_H_INCLUDED

#include "quaternions.h"
#include "vector2f.h"

class vector3f : public vector2f{

public:

union{
    float z;
    float b;
};


vector3f(float xx,float yy,float zz) : z(zz){
    x = xx; y = yy;
}
vector3f(){}

vector3f(const vector3f& vec3){
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
}

vector3f(vector3f&& vec3){
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;

}

void operator=(vector3f vec3){
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
    //return *this;
}

void set_xyz(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}


vector3f cross(vector3f& vec3){
    float x_ = (y * vec3.z) - (z * vec3.y);
    float y_ = (z * vec3.x) - (x * vec3.z);
    float z_ = (x * vec3.y) - (y * vec3.x);
    vector3f res(x_, y_, z_);
  return res;
}


float length(){
    return sqrt((x * x) + (y * y) + (z * z));
}

float dot(vector3f& vec3){
    return ((x * vec3.x) + (y * vec3.y) + (z * vec3.z));
}

vector3f normalized(){
    float length_ = length();
    x /= length_;
    y /= length_;
    z /= length_;

    return (*this);
}

vector3f rotate(float angle, vector3f& axis){
    float halfsinangle = (float)sin((angle*3.1415/180)/2);
    float halfcosangle = (float)cos((angle*3.1415/180)/2);

    float rx = axis.x * halfsinangle;
    float ry = axis.y * halfsinangle;
    float rz = axis.z * halfsinangle;
    float rw = halfcosangle;

    quaternion rotation(rx,ry,rz,rw);
    quaternion conjugate = rotation.conjugate();
    floats a;
    a.x = this->x;
    a.y = this->y;
    a.z = this->z;
    quaternion w = rotation.mult(a).mult(conjugate);

    this->x = w.x;
    this->y = w.y;
    this->z = w.z;

    return *this;
}

vector3f lerp(vector3f& destination, float lerp_factor){
    return ((destination - (*this)) * lerp_factor) + (*this);
}

vector3f add(vector3f vec3){
    x += vec3.x;
    y += vec3.y;
    z += vec3.z;

    return (*this);
}

vector3f add_m(vector3f& vec3){
    return vector3f(x+vec3.x, y+vec3.y, z+vec3.z);
}

vector3f add_m(vector3f&& vec3){
    return vector3f(x+vec3.x, y+vec3.y, z+vec3.z);
}

vector3f operator+(vector3f& vec3){
    return vector3f(x+vec3.x, y+vec3.y, z+vec3.z);
}

vector3f operator+(vector3f&& vec3){
    return vector3f(x+vec3.x, y+vec3.y, z+vec3.z);
}

vector3f add(float r){
    x += r;
    y += r;
    z += r;

    return (*this);
}


vector3f add_m(float r){
    return vector3f(x+r, y+r, z+r);
}


vector3f operator+(float r){
    return vector3f(x+r, y+r, z+r);
}


void sub(vector3f& vec3){
    x -= vec3.x;
    y -= vec3.y;
    z -= vec3.z;
}


vector3f sub_m(vector3f& vec3){
    return vector3f(x-vec3.x, y-vec3.y, z-vec3.z);
}

vector3f operator-(vector3f& vec3){
    return vector3f(x-vec3.x, y-vec3.y, z-vec3.z);
}

vector3f sub(float r){
    x -= r;
    y -= r;
    z -= r;

    return (*this);
}


vector3f sub_m(float r){
    return vector3f(x-r, y-r, z-r);
}


vector3f operator-(float r){
    return vector3f(x-r, y-r, z-r);
}


void mult(vector3f& vec3){
    x *= vec3.x;
    y *= vec3.y;
    z *= vec3.z;
}


vector3f mult_m(vector3f& vec3){
    return vector3f(x*vec3.x, y*vec3.y, z*vec3.z);
}


vector3f operator*(vector3f& vec3){
    return vector3f(x*vec3.x, y*vec3.y, z*vec3.z);
}


/* bootleg */
void mult(floats& vec3){
    x *= vec3.x;
    y *= vec3.y;
    z *= vec3.z;
}

vector3f mult(float r){
    x *= r;
    y *= r;
    z *= r;

    return (*this);
}



vector3f mult_m(float r){
    return vector3f(x*r, y*r, z*r);
}


vector3f operator*(float r){
    return vector3f(x*r, y*r, z*r);
}


void div(vector3f& vec3){
    x /= vec3.x;
    y /= vec3.y;
    z /= vec3.z;
}


vector3f div_m(vector3f& vec3){
    return vector3f(x/vec3.x, y/vec3.y, z/vec3.z);
}


vector3f operator/(vector3f& vec3){
    return vector3f(x/vec3.x, y/vec3.y, z/vec3.z);
}


vector3f div(float r){
    x /= r;
    y /= r;
    z /= r;

    return (*this);
}


vector3f div_m(float r){
    return vector3f(x/r, y/r, z/r);
}


vector3f operator/(float r){
    return vector3f(x/r, y/r, z/r);
}

typedef vector3f vec3;
typedef vector3f rgb;

};


#endif // VECTOR3F_H_INCLUDED
