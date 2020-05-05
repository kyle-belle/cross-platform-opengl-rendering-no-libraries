#ifndef VECTOR2F_H_INCLUDED
#define VECTOR2F_H_INCLUDED

#include <math.h>

#define M_PI		3.14159265358979323846

class vector2f{
public:

union{

    struct{
        float x,y;
    };

    struct{
        float r,g;
    };

};
vector2f(){}

vector2f(float xx, float yy): x(xx), y(yy){

}

~vector2f(){}

vector2f(const vector2f& vec2){
    //printf("copied!");
    this->x = vec2.x;
    this->y = vec2.y;
}

vector2f(vector2f&& vec2){
    //printf("moved!");
    this->x = vec2.x;
    this->y = vec2.y;

}

void operator=(vector2f vec2){
    this->x = vec2.x;
    this->y = vec2.y;
    //return *this;
}
//
//vector2f operator=(vector2f&& vec2){
//    return vector2f(vec2);
//}

float length(){
    return sqrt((x * x) + (y * y));
}

float dot(vector2f vec2){
    return ((x * vec2.x) + (y * vec2.y));
}

float cross(vector2f r){
    return (x * r.y) - (y * r.x);
}

vector2f normalized(){
    float length_ = length();
    x /= length_;
    y /= length_;

    return (*this);
}

vector2f rotate(double angle){
    float radians = (angle * M_PI / 180.0);
    float sine = sin(radians);
    float cosine = cos(radians);

    x = (x * cosine - y * sine);
    y = (x * sine + y * cosine);

    return (*this);
}

vector2f lerp(vector2f& destination, float lerp_factor){
    return ((destination - (*this)) * lerp_factor) + (*this);
}

void add(vector2f& vec2){
    x += vec2.x;
    y += vec2.y;
}


vector2f add_m(vector2f& vec2){
    return vector2f(x+vec2.x, y+vec2.y);
}


vector2f operator+(const vector2f& vec2){
    return vector2f(x+vec2.x, y+vec2.y);
}


vector2f add(float r){
    x += r;
    y += r;

    return (*this);
}


vector2f add_m(float r){
    return vector2f(x-r, y-r);
}


vector2f operator+(float r){
    return vector2f(x-r, y-r);
}


void sub(vector2f& vec2){
    x -= vec2.x;
    y -= vec2.y;
}


vector2f sub_m(vector2f& vec2){
    return vector2f(x-vec2.x, y-vec2.y);
}


vector2f operator-(vector2f& vec2){
    return vector2f(x-vec2.x, y-vec2.y);
}


vector2f sub(float r){
    x -= r;
    y -= r;

    return (*this);
}


vector2f sub_m(float r){
    return vector2f(x-r, y-r);
}


vector2f operator-(float r){
    return vector2f(x-r, y-r);
}


void mult(vector2f&& vec2){
    x *= vec2.x;
    y *= vec2.y;
}


vector2f mult_m(vector2f& vec2){
    return vector2f(x*vec2.x, y*vec2.y);
}


vector2f operator*(vector2f& vec2){
    return vector2f(x*vec2.x, y*vec2.y);
}


vector2f mult(float r){
    x *= r;
    y *= r;

    return (*this);
}


vector2f mult_m(float r){
    return vector2f(x*r, y*r);
}


vector2f operator*(float r){
    return vector2f(x*r, y*r);
}


void div(vector2f& vec2){
    x /= vec2.x;
    y /= vec2.y;
}


vector2f div_m(vector2f& vec2){
    return vector2f(x/vec2.x, y/vec2.y);
}


vector2f operator/(vector2f& vec2){
    return vector2f(x/vec2.x, y/vec2.y);
}


vector2f div(float r){
    x /= r;
    y /= r;

    return (*this);
}


vector2f div_m(float r){
    return vector2f(x/r, y/r);
}

vector2f operator/(float r){
    return vector2f(x/r, y/r);
}

void set_xy(float x, float y){
    this->x = x;
    this->y = y;
}

void set_xy(vector2f& vec2){
    *this = vec2;
}

void set_xy(vector2f&& vec2){
    *this = vec2;
}

};

typedef vector2f vec2;

#endif // VECTOR2F_H_INCLUDED
