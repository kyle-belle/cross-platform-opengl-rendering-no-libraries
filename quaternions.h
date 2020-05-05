#ifndef QUATERNIONS_H_INCLUDED
#define QUATERNIONS_H_INCLUDED


#include "math.h"
//#include "vector3f.h"

struct floats{
    float x,y,z;
};


class quaternion{

public:
float x,y,z,w;

public:
    quaternion(float X, float Y, float Z, float W) : x(X),y(Y),z(Z),w(W){}
    ~quaternion(){}

float length(){
    return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

quaternion normalized(){
    float length_ = length();
    x /= length_;
    y /= length_;
    z /= length_;
    w /= length_;

    return (*this);
}

quaternion conjugate(){
    return quaternion(-x, -y, -z, w);
}


quaternion mult(quaternion& quat){
    float w_ = ((w * quat.w) - (x * quat.x) - (y * quat.y) - (z * quat.z));
    float x_ = ((x * quat.w) + (w * quat.x) + (y * quat.z) - (z * quat.y));
    float y_ = ((y * quat.w) + (w * quat.y) + (z * quat.x) - (x * quat.z));
    float z_ = ((z * quat.w) + (w * quat.z) + (x * quat.y) - (y * quat.x));

    return quaternion(x_, y_, z_, w_);
}

quaternion mult(floats& vec3){
    float w_ = ((-x * vec3.x) - (y * vec3.y) - (z * vec3.z));
    float x_ = ((w * vec3.x) + (y * vec3.z) - (z * vec3.y));
    float y_ = ((w * vec3.y) + (z * vec3.x) - (x * vec3.z));
    float z_ = ((w * vec3.z) + (x * vec3.y) - (y * vec3.x));

    return quaternion(x_, y_, z_, w_);
}

};

#endif // QUATERNIONS_H_INCLUDED
