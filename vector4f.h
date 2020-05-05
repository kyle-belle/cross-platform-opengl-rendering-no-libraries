#ifndef VECTOR4F_H_INCLUDED
#define VECTOR4F_H_INCLUDED

#include "vector3f.h"

class vector4f : public vector3f{

public:

union{
    float w;
    float a;
};

vector4f(){}

vector4f(float xx, float yy, float zz, float ww){
    x = xx;
    y = yy;
    z = zz;
    w = ww;
}

 void set_xyzw(float xx, float yy, float zz, float ww){
    x = xx;
    y = yy;
    z = zz;
    w = ww;
 }

};

typedef vector4f vec4;
typedef vector4f rgba;

#endif // VECTOR4F_H_INCLUDED
