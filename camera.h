#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED


//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
#include "vector3f.h"

//class camera
//{
//    public:
//
// camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){
//        p_perspective = glm::perspective(fov, aspect, zNear, zFar);
//        p_position = pos;
//        p_forward = glm::vec3(0,0,1);
//        p_up = glm::vec3(0,1,0);
//    }
//
//    inline glm::mat4 get_view_projection(){
//        return  p_perspective * p_rotation * glm::lookAt(p_position, p_position + p_forward, p_up);
//    }
//
//    ~camera(){}
//
//
//    void set_camera(glm::vec3& pos){
//        p_position=pos;
//    }
//
//    void rotate(float angle, glm::vec3 axis){
//       p_rotation *= glm::rotate(angle, axis);
//       if(axis.y == 1){
//       //p_forward.y -= axis.y * angle;
//       }
////       if(axis.x == 1)
////       p_up.y += axis.x * angle;
//    }
//
//    glm::mat4 p_perspective;
//    glm::vec3 p_position;
//    glm::vec3 p_forward;
//    glm::vec3 p_up;
//    glm::mat4x4 p_rotation;
//};


class camera{

public:

    vector3f yAXIS = {0,1,0};

    vector3f position;
    vector3f forward;
    vector3f up = yAXIS;

    camera(){
        position.set_xyz(0,0,0);
        forward.set_xyz(0,0,1);
        up.set_xyz(0,1,0);
    }

    camera(vector3f Position, vector3f Forward = vector3f(0,0,1), vector3f Up = vector3f(0,1,0)):position(Position), forward(Forward), up(Up){
        forward.normalized();
        up.normalized();
    }

    void set_camera(camera& camera){
        (*this) = camera;
    }


    void move(vector3f dir, float amount){
        position.add(dir.mult(amount));
    }

    vector3f get_left(){
        vector3f left = forward.cross(up);
        left.normalized();
        return left;
    }

    vector3f get_right(){
       vector3f right = up.cross(forward);
       right.normalized();
       return right;
    }

    void rotate_y(float angle){
        vector3f yaxis = yAXIS;
        vector3f hAXIS = yaxis.cross(forward);

        forward.rotate(angle, yaxis);
        forward.normalized();

        up = forward.cross(hAXIS);
        up.normalized();
    }

    void rotate_x(float angle){
        //if(forward.y > 1.0f)
          //  return;

        vector3f yaxis = yAXIS;
        vector3f hAXIS = yaxis.cross(forward);

        forward.rotate(angle, hAXIS);
        forward.normalized();

        up = forward.cross(hAXIS);
        up.normalized();
    }

    void set_position(vector3f& Position){
        this->position = Position;
    }

    void set_position(float x, float y, float z){
        this->position.x = x;
        this->position.y = y;
        this->position.z = z;
    }

    vector3f get_position(){
        return position;
    }

    void set_forward(vector3f& Forward){
        this->forward = Forward;
    }

    void set_forward(float x, float y, float z){
        this->forward.x = x;
        this->forward.y = y;
        this->forward.z = z;
    }

    vector3f get_forward(){
        return forward;
    }

    void set_up(vector3f& Up){
        this->up = Up;
    }

    void set_up(float x, float y, float z){
        this->up.x = x;
        this->up.y = y;
        this->up.z = z;
    }

    vector3f get_up(){
        return up;
    }

    void set_camera(vector3f& Position, vector3f& Forward, vector3f& Up){
        this->position = Position;
        this->forward = Forward;
        this->up = Up;
    }
};

#endif // CAMERA_H_INCLUDED
