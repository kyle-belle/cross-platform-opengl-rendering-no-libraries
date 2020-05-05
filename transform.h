#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/transform.hpp"
//
#include "vector3f.h"
#include "matrices.h"
#include "camera.h"
//
//
//class transform
//{
//    public:
//        transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(),const glm::vec3& scale = glm::vec3(1.0f,1.0f,1.0f))
//        :c_position(pos), c_rotation(rot), c_scale(scale){}
//        ~transform(){}
//        inline glm::mat4 get_model()const{
//            glm::mat4 position = glm::translate(c_position);
//            glm::mat4 rotation_x = glm::rotate(c_rotation.x, glm::vec3(1.0f,0.0f,0.0f));
//            glm::mat4 rotation_y = glm::rotate(c_rotation.y, glm::vec3(0.0f,1.0f,0.0f));
//            glm::mat4 rotation_z = glm::rotate(c_rotation.z, glm::vec3(0.0f,0.0f,1.0f));
//            glm::mat4 scale = glm::scale(c_scale);
//
//            glm::mat4 rotation = rotation_x * rotation_y * rotation_z;
//
//            return  position * rotation * scale;
//        }
//        inline glm::vec3& get_position(){ return c_position; }
//        inline glm::vec3& get_rotation(){ return c_rotation; }
//        inline glm::vec3& get_scale(){ return c_scale; }
//    protected:
//
//    private:
//        glm::vec3 c_position;
//        glm::vec3 c_rotation;
//        glm::vec3 c_scale;
//
//
//};


class transformation{

public:

static float zNEAR;// = 0.1f;
static float zFAR;// = 1000.0f;
static float FOV;
static int HEIGHT;
static int WIDTH;

static camera Camera;

vector3f translation;
vector3f rotation;
vector3f scale;


matrix4x4 get_transformation(){

    matrix4x4 translation_matrix;
    matrix4x4 rotation_matrix;
    matrix4x4 scale_matrix;

    translation_matrix = translation_matrix.init_translation(translation.x, translation.y, translation.z);
    rotation_matrix = rotation_matrix.init_rotation(rotation.x, rotation.y, rotation.z);
    scale_matrix = scale_matrix.init_scale(scale.x, scale.y, scale.z);

    return translation_matrix.mult(rotation_matrix.mult(scale_matrix));
}


matrix4x4 get_projected_transformation(){

    matrix4x4 transformation_matrix = get_transformation();
    matrix4x4 projection_matrix  = projection_matrix.init_perspective_projection(FOV, HEIGHT, WIDTH, zNEAR, zFAR);
    matrix4x4 camera_rotation = camera_rotation.init_camera(Camera.get_forward(), Camera.get_up());
    matrix4x4 camera_translation = camera_translation.init_translation(-Camera.get_position().x, -Camera.get_position().y, -Camera.get_position().z);


    return projection_matrix.mult(camera_rotation.mult(camera_translation.mult(transformation_matrix)));
}


void set_projection(float fov, float height, float width, float znear, float zfar){

    FOV = fov;
    HEIGHT = height;
    WIDTH = width;
    zNEAR = znear;
    zFAR = zfar;

}

vector3f get_translation(){
    return translation;
}

void set_translation(vector3f& translate){
    translation = translate;
}

void set_translation(float x, float y, float z){
    translation.x = x;
    translation.y = y;
    translation.z = z;
}

vector3f get_rotation(){
    return rotation;
}

void set_rotation(vector3f& rotate){
    this->rotation = rotate;
}

void set_rotation(float x, float y, float z){
    this->rotation.x = x;
    this->rotation.y = y;
    this->rotation.z = z;
}

vector3f get_scale(){
    return scale;
}

void set_scale(vector3f& scale){
    this->scale = scale;
}

void set_scale(float x, float y, float z){
    this->scale.x = x;
    this->scale.y = y;
    this->scale.z = z;
}

void set_camera(camera& camera){
    this->Camera = camera;
}



transformation(){
    Camera.set_position(0,0,0);
    Camera.set_up(0,1,0);
    Camera.set_forward(0,0,1);
    translation.set_xyz(0,0,0);
    rotation.set_xyz(0,0,0);
    scale.set_xyz(1,1,1);
}


};


#endif // TRANSFORM_H_INCLUDED
