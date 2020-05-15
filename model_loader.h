#ifndef MODEL_LOADER_H_INCLUDED
#define MODEL_LOADER_H_INCLUDED

#include <vector>
#include "vector3f.h"
#include "shader.h"
#include "resource_loader.h"

class Model_index{

    public:

        unsigned int vertex_index;
        unsigned int tex_coord_index;
        unsigned int normal_index;

        bool operator ==(const Model_index& other){
//            printf("%p --- %p\n", this, &other);
            return ((other.vertex_index == this->vertex_index) && (other.tex_coord_index == this->tex_coord_index) && (other.normal_index == this->normal_index) && (this != &other));
        }

};

class Object;

class Model_loader : public Resource_loader{
    public:
        /*static*/ unsigned int VAO;
        bool has_uvs = false;
        bool has_normals = false;
        bool object_loaded = false;
        std::vector<vector3f> model_vertices;
        std::vector<vector3f> model_normals;
        std::vector<vector2f> model_tex_coords;
        std::vector<Model_index> model_indices;

        Model_loader(){}
        Model_loader(const char* file);
        Model_loader(const char* file, Object* object);

        void create_model(Object* object);

};

#endif // MODEL_LOADER_H_INCLUDED
