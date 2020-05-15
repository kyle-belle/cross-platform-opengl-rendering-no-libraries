#include <string.h>
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "utils.h"
#include "resource_loader.h"
#include "obj_load.h"
#include "macros.h"
//unsigned int Object::VAO;

#define OBJ_FILE_EXTENTION "obj"
#define COLLADA_FILE_EXTENSION "dae"

Object::Object(const char* file){
    char* extension = get_file_extension(file);
    printf("Object file extension: %s\n", extension);
    if(extension){
        if(strcasecmp(OBJ_FILE_EXTENTION, extension) == STR_MATCH){
            OBJ_loader(file, this);
        }else{
            printf("Unsupported file type .%s\n", extension);
        }
    }else{
        printf("Unknown file type (.%s) no extension present\n", extension);
        return;
    }

    indice_size = this->indices.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(4, buffer_handles);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(OBJECT_VERTEX_BUFFER);
    glVertexAttribPointer(OBJECT_VERTEX_BUFFER, 3, GL_FLOAT, false, 0, 0);


    if(this->has_normals){
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_NORMAL_BUFFER);
        glVertexAttribPointer(OBJECT_NORMAL_BUFFER, 3, GL_FLOAT, false, 0, 0);
    }

    if(this->has_uvs){
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_TEX_COORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords[0]) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_TEX_COORD_BUFFER);
        glVertexAttribPointer(OBJECT_TEX_COORD_BUFFER, 2, GL_FLOAT, false, 0, 0);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handles[OBJECT_INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
    }

Object::Object(float* vertices, unsigned int vert_size, unsigned int* indices, unsigned int ind_size){
//        printf("sizeof(indices) %d\n", ind_size);

        this->vertices.reserve((vert_size/4)/3);

        for (unsigned int i = 0; i < vert_size/4; i+=3){
            this->vertices.emplace_back(vector3f(vertices[i], vertices[i+1], vertices[i+2]));
        }

        //this->vertices = std::vector<vector3f>(vertices, vertices + vert_size);

        this->indices = std::vector<unsigned int>(indices, indices + ind_size);
        indice_size = this->indices.size();

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(4, buffer_handles);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices[0]) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_VERTEX_BUFFER);
        glVertexAttribPointer(OBJECT_VERTEX_BUFFER, 3, GL_FLOAT, false, 0, 0);

//        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_NORMAL_BUFFER]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
//        glEnableVertexAttribArray(OBJECT_NORMAL_BUFFER);
//        glVertexAttribPointer(OBJECT_NORMAL_BUFFER, 3, GL_FLOAT, false, 0, 0);

//        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_TEX_COORD_BUFFER]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords[0]) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW);
//        glEnableVertexAttribArray(OBJECT_TEX_COORD_BUFFER);
//        glVertexAttribPointer(OBJECT_TEX_COORD_BUFFER, 2, GL_FLOAT, false, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handles[OBJECT_INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
}

Object::Object(float* vertices, unsigned int vert_size, float* tex_coords, unsigned int tex_size, unsigned int* indices, unsigned int ind_size){
        printf("sizeof(indices) %d\n", ind_size);
        this->vertices.reserve((vert_size/4)/3);

        for (unsigned int i = 0; i < vert_size/4; i+=3){
            this->vertices.emplace_back(vector3f(vertices[i], vertices[i+1], vertices[i+2]));
        }

        this->tex_coords.reserve((tex_size/4)/2);

        for (unsigned int i = 0; i < tex_size/4; i+=2){
            this->tex_coords.emplace_back(vector2f(tex_coords[i], tex_coords[i+1]));
        }

        //this->vertices = std::vector<vector3f>(vertices, vertices + vert_size);

        this->indices = std::vector<unsigned int>(indices, indices + ind_size/4);

        indice_size = this->indices.size();


        printf("sizeof(indices) %lu\n", this->indices.size());
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(4, buffer_handles);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices[0]) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_VERTEX_BUFFER);
        glVertexAttribPointer(OBJECT_VERTEX_BUFFER, 3, GL_FLOAT, false, 0, 0);

//        if(this->has_normals)
//        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_NORMAL_BUFFER]);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
//        glEnableVertexAttribArray(OBJECT_NORMAL_BUFFER);
//        glVertexAttribPointer(OBJECT_NORMAL_BUFFER, 3, GL_FLOAT, false, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_TEX_COORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->tex_coords[0]) * this->tex_coords.size(), &this->tex_coords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_TEX_COORD_BUFFER);
        glVertexAttribPointer(OBJECT_TEX_COORD_BUFFER, 2, GL_FLOAT, false, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handles[OBJECT_INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
}

Object::Object(Object& other): has_uvs(other.has_uvs), has_normals(other.has_normals), vertices(other.vertices), normals(other.normals), tex_coords(other.tex_coords), indices(other.indices), indice_size(other.indice_size){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(4, buffer_handles);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(OBJECT_VERTEX_BUFFER);
    glVertexAttribPointer(OBJECT_VERTEX_BUFFER, 3, GL_FLOAT, false, 0, 0);


    if(this->has_normals){
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_NORMAL_BUFFER);
        glVertexAttribPointer(OBJECT_NORMAL_BUFFER, 3, GL_FLOAT, false, 0, 0);
    }

    if(this->has_uvs){
        glBindBuffer(GL_ARRAY_BUFFER, buffer_handles[OBJECT_TEX_COORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords[0]) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(OBJECT_TEX_COORD_BUFFER);
        glVertexAttribPointer(OBJECT_TEX_COORD_BUFFER, 2, GL_FLOAT, false, 0, 0);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_handles[OBJECT_INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices[0]) * this->indices.size(), &this->indices[0], GL_STATIC_DRAW);
}

Object::Object(Object&& other): VAO(other.VAO), has_uvs(other.has_uvs), has_normals(other.has_normals), vertices(std::move(other.vertices)), normals(std::move(other.normals)), tex_coords(std::move(other.tex_coords)), indices(std::move(other.indices)), indice_size(other.indice_size){
    memcpy(this->buffer_handles, other.buffer_handles, 4);
}

void Object::create_object(std::vector<vector3f>& model_vertices, std::vector<vector2f>& model_tex_coords, std::vector<vector3f>& model_normals, std::vector<Model_index>& model_indices){

//    obj_index current_index;
//    unsigned int current = 0;
    for(unsigned int i = 0; i < model_indices.size(); i++){
//        current_index = model_indices[i];

//        printf("obj vert: %f\n ", this->model_vertices[this->model_indices[i].vertex_index].x);
//        printf("index %d\n", this->model_indices[i].vertex_index);
//        printf("before vert %u, vert_size:%d, obj_indices_size:%d\n", this->model_indices[i].vertex_index, this->model_vertices.size(), this->model_indices.size());

//        if(std::find(this->model_indices.begin(), this->model_indices.end(), this->model_indices[i]) == this->model_indices.end()){

//        int previous_index = -1;
//        for (unsigned int j = 0; j < i; j++){
//            if (model_indices[i] == model_indices[j]){
//                printf("i = %u/%u/%u, j = %u/%u/%u\n", i - j, j, model_indices[i].normal_index, model_indices[j].vertex_index, model_indices[j].tex_coord_index, model_indices[j].normal_index);
//                previous_index = j;
//                break;
//            }
//        }
//
//        if(previous_index > -1){
//            indices.push_back(indices[previous_index]);
//        }else{

            this->vertices.emplace_back(model_vertices[model_indices[i].vertex_index]);

    //        printf("before tex %u, tex_size:%d, obj_indices_size:%d\n", this->model_indices[i].tex_coord_index, this->modal_tex_coords.size(), this->model_indices.size());
            if(this->has_uvs){
    //            printf("tex #%d\tx: %f, y: %f, z: %f\n", i, this->modal_tex_coords[this->model_indices[i].tex_coord_index].x, this->modal_tex_coords[this->model_indices[i].tex_coord_index].y);
                this->tex_coords.emplace_back(model_tex_coords[model_indices[i].tex_coord_index]);
            }

            if(this->has_normals){
                this->normals.emplace_back(model_normals[model_indices[i].normal_index]);
            }

            this->indices.push_back(i);

//            current++;
//        }
//        }

    }
    this->object_loaded = true;
}

void Object::draw(shader& shader){

    shader.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indice_size, UNSIGNED_INT, 0);
}
