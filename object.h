#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <vector>
#include <array>
#include <string.h>
#include "GL/glew.h"
#include "shader.h"
#include "vector3f.h"
#include "obj_loader.h"
#include "model_loader.h"

#define OBJECT_VERTEX_BUFFER 0
#define OBJECT_NORMAL_BUFFER 1
#define OBJECT_TEX_COORD_BUFFER 2
#define OBJECT_INDEX_BUFFER 3

#define FLOAT GL_FLOAT
#define UNSIGNED_INT GL_UNSIGNED_INT

class Object{

    public:

        /* static */ unsigned int VAO;
        bool has_uvs = false;
        bool has_normals = false;

        unsigned int buffer_handles[4];
        std::vector<vector3f> vertices;
        std::vector<vector3f> normals;
        std::vector<vector2f> tex_coords;
        std::vector<unsigned int> indices;
        unsigned int indice_size;
        bool object_loaded = false;



        Object() = default;
        Object(const char* file);
        Object(float* vertices, unsigned int vert_size, unsigned int* indices, unsigned int ind_size);
        Object(float* vertices, unsigned int vert_size, float* tex_coords, unsigned int tex_size, unsigned int* indices, unsigned int ind_size);
        Object(Object& other);
        Object(Object&&);

        ~Object() = default;

        void create_object(std::vector<vector3f>& obj_vertices, std::vector<vector2f>& obj_tex_coords, std::vector<vector3f>& obj_normals, std::vector<Model_index>& obj_indices);
        void draw(shader& shader);

        void buffer_data(const IndexedModel& model){
            indice_size = model.indices.size();

            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(4, buffer_handles);

            glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_VERTEX_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(OBJECT_VERTEX_BUFFER);
            glVertexAttribPointer(OBJECT_VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_TEX_COORD_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(OBJECT_TEX_COORD_BUFFER);
            glVertexAttribPointer(OBJECT_TEX_COORD_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_NORMAL_BUFFER]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(OBJECT_NORMAL_BUFFER);
            glVertexAttribPointer(OBJECT_NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handles[OBJECT_INDEX_BUFFER]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

            glBindVertexArray(0);
        }
};

#endif // OBJECT_H_INCLUDED
