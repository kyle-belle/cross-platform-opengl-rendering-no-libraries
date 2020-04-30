#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <vector>
#include <array>
#include <string.h>
#include "GL/glew.h"
#include "shader.h"
#include "vector3f.h"

#define OBJECT_VERTEX_BUFFER 0
#define OBJECT_NORMAL_BUFFER 1
#define OBJECT_TEX_COORD_BUFFER 2
#define OBJECT_INDEX_BUFFER 3

#define FLOAT GL_FLOAT
#define UNSIGNED_INT GL_UNSIGNED_INT

class obj_index{

    public:

        unsigned int vertex_index;
        unsigned int tex_coord_index;
        unsigned int normal_index;

};

class obj_parse_helper{
    public:

        char face_line[64];
        char face_value[16];
        char face_vert[4][8];
        char face_uv[4][8];
        char face_norm[4][8];

        obj_index temp_obj_index;

        //bool has_uvs = false, has_normals = false;

        unsigned int start_line_index;
        unsigned int start_value_index;

        unsigned int end_line_index;
        unsigned int end_value_index;

        unsigned int line_seperator;
        unsigned int value_seperator;

        void parse_face_value(unsigned int index, bool& has_uvs, bool& has_normals){
            unsigned int i;
            for(i = start_value_index; i < end_value_index; i++){

                if(face_value[i] == '/' || i == (end_value_index - 1)){
//
                    value_seperator = i;
                    memcpy(face_vert[index], &face_value[start_value_index], value_seperator);
                    face_vert[index][value_seperator] = '\0';

                    temp_obj_index.vertex_index = ((atoi(face_vert[index])) - 1);

                    if(face_value[value_seperator] == '/'){
                        has_uvs = true;
//                        printf("has uvs\n");
                    }

                    //printf("face_vert: %d\n", atoi(face_vert[index]));
                    break;
                }
            }

            start_value_index = value_seperator + 1;
////////////////////////////////////////////////////////
            if(has_uvs){

                for(i = start_value_index; i < end_value_index; i++){
                    if(face_value[i] == '/' || i == (end_value_index - 1)){
//                                    printf("uv i: %d\n", i);
                        value_seperator = i;
                        memcpy(face_uv[index], &face_value[start_value_index], value_seperator);
                        face_uv[index][value_seperator] = '\0';

                        temp_obj_index.tex_coord_index = atoi(face_uv[index]) - 1;

                        if(face_value[value_seperator] == '/'){
                            has_normals = true;
//                            printf("has normals\n");
                        }
                        //printf("face_uv: %d\n", atoi(face_uv[index]));
                    }
                }
            }

            start_value_index = value_seperator + 1;
///////////////////////////////////////////////////////////////
            if(has_normals){

                for(i = start_value_index; i < end_value_index; i++){

                    if(face_value[i] == '/' || i == end_value_index - 1){
//                        printf("norm i: %d\n", i);
                        value_seperator = i;
                        memcpy(face_norm[index], &face_value[start_value_index], value_seperator);
                        face_norm[index][value_seperator] = '\0';

                        temp_obj_index.normal_index = atoi(face_norm[index]) - 1;
//                        if(temp_obj_index.normal_index > 13710){
//                            printf("face_norm: %d, %s\n", temp_obj_index.normal_index, face_norm);
//                        }
                    }
                }
            }
        }

        void parse_face(const char* face, unsigned int face_length, std::vector<obj_index>& obj_indices, bool& has_uvs, bool& has_normals){
            unsigned int i;
            start_value_index = 0;
            start_line_index = 0;
//            end_line_index = face_length;

            for(i = start_line_index; i < face_length; i++){
                if(face[i] == ' '){
                    end_line_index = i;
                    break;
                }
            }

            if(end_line_index < face_length){

                end_value_index = end_line_index - start_line_index;
                //printf("end - start: %d\n", end_ - start);
                memcpy(face_value, &face[start_line_index], end_value_index);
                face_value[end_value_index] = '\0';
                //printf("\nface_value: %s\n", face_value);

////////////////////////////////////////////////////////////////////

                parse_face_value(0, has_uvs, has_normals);

                obj_indices.emplace_back(temp_obj_index);

//                for(i = start_value_index; i < end_value_index; i++){
//
//                    if(face_value[i] == '/' || i == end_value_index - 1){
////
//                        value_seperator = i;
//                        memcpy(face_vert[0], &face_value[start_value_index], value_seperator);
//                        face_vert[0][value_seperator] = '\0';
//
//                        temp_obj_index.vertex_index = atoi(face_vert[0]);
//
//                        if(face_value[value_seperator] == '/'){
//                            has_uvs = true;
//                            printf("has uvs\n");
//                        }
//
//                        printf("face_vert: %d\n", atoi(face_vert[0]));
//                        break;
//                    }
//                }
//
//                start_value_index = value_seperator + 1;
//////////////////////////////////////////////////////////
//                if(has_uvs){
//
//                    for(i = start_value_index; i < end_value_index; i++){
//                        if(face_value[i] == '/' || i == end_value_index - 1){
////                                    printf("uv i: %d\n", i);
//                            value_seperator = i;
//                            memcpy(face_uv[0], &face_value[start_value_index], value_seperator);
//                            face_uv[0][value_seperator] = '\0';
//
//                            temp_obj_index.tex_coord_index = atoi(face_uv[0]);
//
//                            if(face_value[value_seperator] == '/'){
//                                has_normals = true;
//                                printf("has normals\n");
//                            }
//                            printf("face_uv: %d\n", atoi(face_uv[0]));
//                        }
//                    }
//                }
//
//                start_value_index = value_seperator + 1;
/////////////////////////////////////////////////////////////////
//                if(has_normals){
//
//                    for(i = start_value_index; i < end_value_index; i++){
//
//                        if(face_value[i] == '/' || i == end_value_index - 1){
//                            printf("norm i: %d\n", i);
//                            value_seperator = i;
//                            memcpy(face_norm[0], &face_value[start_value_index], value_seperator);
//                            face_norm[0][value_seperator] = '\0';
//
//                            temp_obj_index.normal_index = atoi(face_norm[0]);
//                            printf("face_norm: %d\n", atoi(face_norm[0]));
//                        }
//                    }
//                }
//
            }


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
                start_line_index = end_line_index + 1;
                start_value_index = 0;
                for(i = start_line_index; i < face_length; i++){
                    if(face[i] == ' '){
                        end_line_index = i;
                        break;
                    }
                }

                if(end_line_index < face_length){
                    end_value_index = end_line_index - start_line_index;
                    //printf("end - start: %d\n", end - start);
                    memcpy(face_value, &face[start_line_index], end_value_index);
                    face_value[end_value_index] = '\0';
                    //printf("\nface_value: %s\n", face_value);

////////////////////////////////////////////////////////////////////

                    parse_face_value(1, has_uvs, has_normals);

                    obj_indices.emplace_back(temp_obj_index);

//                    for(i = start_value_index; i < end_value_index; i++){
//
//                        if(face_value[i] == '/' || i == end_value_index - 1){
//                            printf("vert i: %d\n", i);
//                            value_seperator = i;
//                            memcpy(face_vert[1], &face_value[start_value_index], value_seperator);
//                            face_vert[1][value_seperator] = '\0';
//                            printf("face_vert: %s\n", face_vert[1]);
//
//                            temp_obj_index.vertex_index = atoi(face_vert[1]);
//
//                            if(face_value[value_seperator] == '/'){
//                                has_uvs = true;
//                                printf("has uvs\n");
//                            }
//
//                            printf("face_vert: %d\n", atoi(face_vert[1]));
//                            break;
//                        }
//                    }
//
//                    start_value_index = value_seperator + 1;
//////////////////////////////////////////////////////////
//                    if(has_uvs){
//
//                        for(i = start_value_index; i < end_value_index; i++){
//                            if(face_value[i] == '/' || i == end_value_index - 1){
//                                printf("uv i: %d\n", i);
//                                value_seperator = i;
//                                memcpy(face_uv[1], &face_value[start_value_index], value_seperator);
//                                face_uv[1][value_seperator] = '\0';
//
//                                temp_obj_index.tex_coord_index = atoi(face_uv[1]);
//
//                                if(face_value[value_seperator] == '/'){
//                                    has_normals = true;
//                                    printf("has normals\n");
//                                }
//                                printf("face_uv: %d\n", atoi(face_uv[1]));
//                            }
//                        }
//                    }
//
//                    start_value_index = value_seperator + 1;
/////////////////////////////////////////////////////////////////
//                    if(has_normals){
//
//                        for(i = start_value_index; i < end_value_index; i++){
//
//                            if(face_value[i] == '/' || i == end_value_index - 1){
//                                printf("norm i: %d\n", i);
//                                value_seperator = i;
//                                memcpy(face_norm[1], &face_value[start_value_index], value_seperator);
//                                face_norm[1][value_seperator] = '\0';
//
//                                temp_obj_index.vertex_index = atoi(face_norm[1]);
//                                printf("norm index: %d\n", atoi(face_norm[1]));
//                            }
//                        }
//                    }
                }
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////
                start_line_index = end_line_index + 1;
                start_value_index = 0;

                for(i = start_line_index; i < face_length; i++){
                    if(face[i] == ' '){
                        end_line_index = i;
                        break;
                    }
                    end_line_index = i;
                }

                if(end_line_index <= face_length){
                    end_value_index = end_line_index - start_line_index;
//                    printf("end - start: %d\n", end_value_index);
                    memcpy(face_value, &face[start_line_index], end_value_index);
                    face_value[end_value_index] = '\0';
                    //printf("\nface_value: %s\n", face_value);

////////////////////////////////////////////////////////////////////

                    parse_face_value(2, has_uvs, has_normals);

                    obj_indices.emplace_back(temp_obj_index);

//                    for(i = start_value_index; i < end_value_index; i++){
//
//                        if(face_value[i] == '/' || i == end_value_index - 1){
//                            printf("vert i: %d\n", i);
//                            value_seperator = i;
//                            memcpy(face_vert[2], &face_value[start_value_index], value_seperator);
//                            face_vert[2][value_seperator] = '\0';
//                            printf("face_vert: %s\n", face_vert[2]);
//
//                            temp_obj_index.vertex_index = atoi(face_vert[2]);
//
//                            if(face_value[value_seperator] == '/'){
//                                has_uvs = true;
//                                printf("has uvs\n");
//                            }
//
//                            printf("face_vert: %d\n", atoi(face_vert[2]));
//                            break;
//                        }
//                    }
//
//                    start_value_index = value_seperator + 1;
//////////////////////////////////////////////////////////
//                    if(has_uvs){
//
//                        for(i = start_value_index; i < end_value_index; i++){
//                            if(face_value[i] == '/' || i == end_value_index - 1){
//                                printf("uv i: %d\n", i);
//                                value_seperator = i;
//                                memcpy(face_uv[2], &face_value[start_value_index], value_seperator);
//                                face_uv[2][value_seperator] = '\0';
//
//                                temp_obj_index.tex_coord_index = atoi(face_uv[2]);
//
//                                if(face_value[value_seperator] == '/'){
//                                    has_normals = true;
//                                    printf("has normals\n");
//                                }
//                                printf("face_uv: %d\n", atoi(face_uv[2]));
//                            }
//                        }
//                    }
//
//                    start_value_index = value_seperator + 1;
/////////////////////////////////////////////////////////////////
//                    if(has_normals){
//
//                        for(i = start_value_index; i < end_value_index; i++){
//
//                            if(face_value[i] == '/' || i == end_value_index - 1){
//                                printf("norm i: %d\n", i);
//                                value_seperator = i;
//                                memcpy(face_norm[2], &face_value[start_value_index], value_seperator);
//                                face_norm[2][value_seperator] = '\0';
//
//                                temp_obj_index.vertex_index = atoi(face_norm[2]);
//                                printf("face_norm: %d\n", atoi(face_norm[2]));
//                            }
//                        }
//                    }
                }

/// ////////////////////////////////////////////////////////////////////////////

                if(end_line_index + 1 < face_length){
                    temp_obj_index.vertex_index = ((atoi(face_vert[0])) - 1);

                    if(has_uvs){
                        temp_obj_index.tex_coord_index = atoi(face_uv[0]) - 1;
                    }

                    if(has_normals){
                        temp_obj_index.normal_index = atoi(face_norm[0]) - 1;
                    }

                    obj_indices.emplace_back(temp_obj_index);

                    temp_obj_index.vertex_index = ((atoi(face_vert[2])) - 1);
                    if(has_uvs){
                        temp_obj_index.tex_coord_index = atoi(face_uv[2]) - 1;
                    }

                    if(has_normals){
                        temp_obj_index.normal_index = atoi(face_norm[2]) - 1;
                    }

                    obj_indices.emplace_back(temp_obj_index);

                    start_line_index = end_line_index + 1;
                    start_value_index = 0;

//                    printf("start_line_index: %d\n", start_line_index);

//                    for(i = start_line_index; i < length; i++){
//                        if(face[i] == ' '||){
//                            end_line_index = i;
//                            break;
//                        }
//                    }

                    if(end_line_index <= face_length){
                        end_value_index = face_length - start_line_index;
//                        printf("end - start: %d\n", end_value_index);
                        memcpy(face_value, &face[start_line_index], end_value_index);
                        face_value[end_value_index] = '\0';
                        //printf("\nface_value: %s\n", face_value);

    ////////////////////////////////////////////////////////////////////

                        parse_face_value(3, has_uvs, has_normals);

                        obj_indices.emplace_back(temp_obj_index);

//                        for(i = start_value_index; i < end_value_index; i++){
//
//                            if(face_value[i] == '/' || i == end_value_index - 1){
//                                printf("vert i: %d\n", i);
//                                value_seperator = i;
//                                memcpy(face_vert[3], &face_value[start_value_index], value_seperator);
//                                face_vert[3][value_seperator] = '\0';
//                                printf("face_vert: %s\n", face_vert[3]);
//
//                                temp_obj_index.vertex_index = atoi(face_vert[3]);
//
//                                if(face_value[value_seperator] == '/'){
//                                    has_uvs = true;
//                                    printf("has uvs\n");
//                                }
//
//                                printf("face_vert: %d\n", atoi(face_vert[3]));
//                                break;
//                            }
//                        }
//
//                        start_value_index = value_seperator + 1;
//    ////////////////////////////////////////////////////////
//                        if(has_uvs){
//
//                            for(i = start_value_index; i < end_value_index; i++){
//                                if(face_value[i] == '/' || i == end_value_index - 1){
//                                    printf("uv i: %d\n", i);
//                                    value_seperator = i;
//                                    memcpy(face_uv[3], &face_value[start_value_index], value_seperator);
//                                    face_uv[3][value_seperator] = '\0';
//
//                                    temp_obj_index.tex_coord_index = atoi(face_uv[3]);
//
//                                    if(face_value[value_seperator] == '/'){
//                                        has_normals = true;
//                                        printf("has normals\n");
//                                    }
//                                    printf("face_uv: %d\n", atoi(face_uv[3]));
//                                }
//                            }
//                        }
//
//                        start_value_index = value_seperator + 1;
//    ///////////////////////////////////////////////////////////////
//                        if(has_normals){
//
//                            for(i = start_value_index; i < end_value_index; i++){
//
//                                if(face_value[i] == '/' || i == end_value_index - 1){
//                                    printf("norm i: %d\n", i);
//                                    value_seperator = i;
//                                    memcpy(face_norm[3], &face_value[start_value_index], value_seperator);
//                                    face_norm[3][value_seperator] = '\0';
//
//                                    temp_obj_index.vertex_index = atoi(face_norm[3]);
//                                    printf("face_norm: %d\n", atoi(face_norm[3]));
//                                }
//                            }
//                        }
                    }
                }
        }

};

class object{

    public:

        bool has_uvs = false;
        bool has_normals = false;

        unsigned int buffer_handles[4];
        /* static */ unsigned int VAO;
        std::vector<vector3f> vertices;
        std::vector<vector3f> normals;
        std::vector<vector2f> tex_coords;
        std::vector<unsigned int> indices;

        std::vector<vector3f> obj_vertices;
        std::vector<vector3f> obj_normals;
        std::vector<vector2f> obj_tex_coords;
        std::vector<obj_index> obj_indices;



        object() = default;
        object(const char* file);
        object(float* vertices, unsigned int vert_size, unsigned int* indices, unsigned int ind_size);
        object(float* vertices, unsigned int vert_size, float* tex_coords, unsigned int tex_size, unsigned int* indices, unsigned int ind_size);

        ~object() = default;

        void create_object();
        void draw(shader& shader);
};

#endif // OBJECT_H_INCLUDED