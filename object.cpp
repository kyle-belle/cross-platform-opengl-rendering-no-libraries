#include <string.h>
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "utils.h"
//unsigned int Object::VAO;

Object::Object(const char* file){
    FILE* obj_file;
    obj_parse_helper face_parser;
    unsigned int i=0;//, start, end, seperator; // , j,k;
    char token;
//    char face_index[16];
//    char vert_index[8];
//    char uv_index[8];
//    char norm_index[8];
    char face[128];
    unsigned int index_length;

//    bool has_uvs = false, has_normals = false;

//    obj_index temp_obj_index[2];


    vector3f vert;
    vector3f norm;
    vector2f tex_;

//    int count = 0;

    obj_file = fopen(file, "r");

    if(obj_file){

        while(file[i]!= '.' || i==0){
            if(i>=strlen(file)){
                printf("filename not valid!\n");
                return ;
            }
            i++;
        }

        if(file[i+1] != 'o' || file[i+2] != 'b' || file[i+3] != 'j'){
            printf("file format (\".%c%c%c\") not supported!\n",file[i+1],file[i+2],file[i+3]);
            return;
        }
        // TODO: load OBJ

        while(!feof(obj_file)){

            token = fgetc(obj_file);

            switch(token){

                case 'v':

                    switch(fgetc(obj_file)){

                        case ' ':
//                            count++;
//                            printf("count: %d\n", count);
                            //fgets(face, 62, obj_file);
                            //face[63] = '\0';
                            //printf("v: %s", face);
                            fscanf(obj_file, "%f %f %f", &vert.x, &vert.y, &vert.z);
//                            printf("Vs1 %f, %f, %f\n", vert.x, vert.y, vert.z);
                            this->obj_vertices.emplace_back(vector3f(vert.x, vert.y, vert.z));
                            //printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        case 'n':

                            fscanf(obj_file, "%f %f %f", &norm.x, &norm.y, &norm.z);
                            this->obj_normals.emplace_back(vector3f(norm.x, norm.y, norm.z));
                            //printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        case 't':

                            fscanf(obj_file, "%f %f", &tex_.x, &tex_.y);
                            this->obj_tex_coords.emplace_back(vector2f(tex_.x, tex_.y));
                            //printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        default:
                            printf("something not right\n");

                    }
                break;

                case 'f':

                //printf("fgetc(obj_file): %c\n", fgetc(obj_file));
                fgetc(obj_file);
                fscanf(obj_file, "%[^\n]s", face);
//                fflush(obj_file);
                    //fgets(face, 25, obj_file);

                    //printf("face:%s\n", face);

                    r_trim(r_trim(r_trim(face, '\r'), '\n'));
                    index_length = strlen(face);
//                    printf("strlen(face): %d\n", index_length);
//                    printf("face: %s\n", face);

                    face_parser.parse_face(/*r_trim(*/face/*)*/, index_length, this->obj_indices, this->has_uvs, this->has_normals);
                    fgetc(obj_file);
//
//                    start = 0;
//                    end = 0;
//
//                    for(i = start; i < index_length; i++){
//                        if(face[i] == ' '){
//                            end = i;
//                            break;
//                        }
//                    }
//
//                    if(end < index_length){
//
//                        printf("end - start: %d\n", end - start);
//                        memcpy(face_index, &face[start], end - start);
//                        face_index[end] = '\0';
//                        printf("face_index: %s\n", face_index);
//
//////////////////////////////////////////////////////////////////////
//                        for(i = start; i < end; i++){
//
//                            if(face_index[i] == '/' || i == end - 1){
////                                printf("vert i: %d\n", i);
//                                seperator = i;
//                                memcpy(vert_index, &face_index[start], seperator);
//                                vert_index[seperator] = '\0';
//
//                                temp_obj_index.vertex_index = atoi(vert_index);
//
//                                if(face_index[seperator] == '/'){
//                                    has_uvs = true;
//                                    printf("has uvs\n");
//                                }
//
//                                printf("vert_index: %d\n", atoi(vert_index));
//                                break;
//                            }
//                        }
//
//                        start = seperator + 1;
// ////////////////////////////////////////////////////////
//                        if(has_uvs){
//
//                            for(i = start; i < end; i++){
//                                if(face_index[i] == '/' || i == end - 1){
////                                    printf("uv i: %d\n", i);
//                                    seperator = i;
//                                    memcpy(uv_index, &face_index[start], seperator);
//                                    uv_index[seperator] = '\0';
//
//                                    temp_obj_index.tex_coord_index = atoi(uv_index);
//
//                                    if(face_index[seperator] == '/'){
//                                        has_normals = true;
//                                        printf("has normals\n");
//                                    }
//                                    printf("uv_index: %d\n", atoi(uv_index));
//                                }
//                            }
//                        }
//
//                        start = seperator + 1;
/////////////////////////////////////////////////////////////////
//                        if(has_normals){
//
//                            for(i = start; i < end; i++){
//
//                                if(face_index[i] == '/' || i == end - 1){
//                                    printf("norm i: %d\n", i);
//                                    seperator = i;
//                                    memcpy(norm_index, &face_index[start], seperator);
//                                    norm_index[seperator] = '\0';
//
//                                    temp_obj_index.vertex_index = atoi(norm_index);
//                                }
//                            }
//                        }
//
//                        start = end + 1;
//
//                        for(i = start; i < index_length; i++){
//                            if(face[i] == ' '){
//                                end = i;
//                                break;
//                            }
//                        }
//
//                        if(end < index_length){
//
//                            printf("end - start: %d\n", end - start);
//                            memcpy(face_index, &face[start], end - start);
//                            face_index[end - start] = '\0';
//                            printf("face_index: %s\n", face_index);
//
//    ////////////////////////////////////////////////////////////////////
//
//                            for(i = start-start; i < end - start; i++){
//
//                                start = 0;
//                                if(face_index[i] == '/' || i == end-start - 1){
//                                    printf("vert i: %d\n", i);
//                                    seperator = i;
//                                    memcpy(vert_index, &face_index[start], seperator);
//                                    vert_index[seperator] = '\0';
//                                    printf("vert_index: %s\n", vert_index);
//
//                                    temp_obj_index.vertex_index = atoi(vert_index);
//
//                                    if(face_index[seperator] == '/'){
//                                        has_uvs = true;
//                                        printf("has uvs\n");
//                                    }
//
//                                    printf("vert_index: %d\n", atoi(vert_index));
//                                    break;
//                                }
//                            }
//
//                            start = seperator + 1;
//     ////////////////////////////////////////////////////////
//                            if(has_uvs){
//
//                                for(i = start; i < end - start; i++){
//                                    if(face_index[i] == '/' || i == end-start - 1){
//                                        printf("uv i: %d\n", i);
//                                        seperator = i;
//                                        memcpy(uv_index, &face_index[start], seperator);
//                                        uv_index[seperator] = '\0';
//
//                                        temp_obj_index.tex_coord_index = atoi(uv_index);
//
//                                        if(face_index[seperator] == '/'){
//                                            has_normals = true;
//                                            printf("has normals\n");
//                                        }
//                                        printf("uv_index: %d\n", atoi(uv_index));
//                                    }
//                                }
//                            }
//
//                            start = seperator + 1;
//    ///////////////////////////////////////////////////////////////
//                            if(has_normals){
//
//                                for(i = start; i < end - start; i++){
//
//                                    if(face_index[i] == '/' || i == end-start - 1){
//                                        printf("norm i: %d\n", i);
//                                        seperator = i;
//                                        memcpy(norm_index, &face_index[start], seperator);
//                                        norm_index[seperator] = '\0';
//
//                                        temp_obj_index.vertex_index = atoi(norm_index);
//                                        printf("norm index: %d\n", atoi(norm_index));
//                                    }
//                                }
//                            }
//                        }
//
//                        start = end +1;
//
//                        for(i = start; i < index_length; i++){
//                            if(face[i] == ' '){
//                                end = i;
//                                break;
//                            }
//                        }
//
//                        if(end < index_length){
//
//                            printf("end - start: %d\n", end - start);
//                            memcpy(face_index, &face[start], end - start);
//                            face_index[end - start] = '\0';
//                            printf("face_index: %s\n", face_index);
//
//    ////////////////////////////////////////////////////////////////////
//
//                            for(i = start-start; i < end - start; i++){
//
//                                start = 0;
//                                if(face_index[i] == '/' || i == end-start - 1){
//                                    printf("vert i: %d\n", i);
//                                    seperator = i;
//                                    memcpy(vert_index, &face_index[start], seperator);
//                                    vert_index[seperator] = '\0';
//                                    printf("vert_index: %s\n", vert_index);
//
//                                    temp_obj_index.vertex_index = atoi(vert_index);
//
//                                    if(face_index[seperator] == '/'){
//                                        has_uvs = true;
//                                        printf("has uvs\n");
//                                    }
//
//                                    printf("vert_index: %d\n", atoi(vert_index));
//                                    break;
//                                }
//                            }
//
//                            start = seperator + 1;
//     ////////////////////////////////////////////////////////
//                            if(has_uvs){
//
//                                for(i = start; i < end - start; i++){
//                                    if(face_index[i] == '/' || i == end-start - 1){
//                                        printf("uv i: %d\n", i);
//                                        seperator = i;
//                                        memcpy(uv_index, &face_index[start], seperator);
//                                        uv_index[seperator] = '\0';
//
//                                        temp_obj_index.tex_coord_index = atoi(uv_index);
//
//                                        if(face_index[seperator] == '/'){
//                                            has_normals = true;
//                                            printf("has normals\n");
//                                        }
//                                        printf("uv_index: %d\n", atoi(uv_index));
//                                    }
//                                }
//                            }
//
//                            start = seperator + 1;
//    ///////////////////////////////////////////////////////////////
//                            if(has_normals){
//
//                                for(i = start; i < end - start; i++){
//
//                                    if(face_index[i] == '/' || i == end-start - 1){
//                                        printf("norm i: %d\n", i);
//                                        seperator = i;
//                                        memcpy(norm_index, &face_index[start], seperator);
//                                        norm_index[seperator] = '\0';
//
//                                        temp_obj_index.vertex_index = atoi(norm_index);
//                                        printf("norm index: %d\n", atoi(norm_index));
//                                    }
//                                }
//                            }
//                        }
//
//                        start = end +1;
//                        if(start < index_length){
//
//                            printf("start %d\n", start);
//                        }
//
//
//
//
//
////                    indices.emplace_back(i);
////                    indices.emplace_back(j);
////                    indices.emplace_back(k);
//                        printf("fgetc(obj_file) case: 'f': %c\n", fgetc(obj_file));
                break;

                default:
                    fgets(face, 127, obj_file);
//                    printf("fgets(face, 25, obj_file): %s\n", fgets(face, 62, obj_file));

                }
            }
            fclose(obj_file);
        }


    create_object();

//    printf("sizeof(indices) %d\n", this->indices.size());
//    printf("sizeof(indices) %d\n", this->obj_indices.size());
//    printf("sizeof(vertices) %d\n", this->obj_vertices.size());
//    printf("sizeof(tex_coords) %d\n", this->obj_tex_coords.size());
//    printf("sizeof(normals) %d\n", this->obj_normals.size());
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
        printf("sizeof(obj indices) %lu\n", this->obj_indices.size());
        printf("sizeof(vertices) %lu\n", this->obj_vertices.size());
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

void Object::create_object(){

//    obj_index current_index;
//    unsigned int current = 0;
    for(unsigned int i = 0; i < this->obj_indices.size(); i++){
//        current_index = obj_indices[i];

//        printf("obj vert: %f\n ", this->obj_vertices[this->obj_indices[i].vertex_index].x);
//        printf("index %d\n", this->obj_indices[i].vertex_index);
//        printf("before vert %u, vert_size:%d, obj_indices_size:%d\n", this->obj_indices[i].vertex_index, this->obj_vertices.size(), this->obj_indices.size());

//        if(std::find(this->obj_indices.begin(), this->obj_indices.end(), this->obj_indices[i]) == this->obj_indices.end()){

//        int previous_index = -1;
//        for (unsigned int j = 0; j < i; j++){
//            if (obj_indices[i] == obj_indices[j]){
//                printf("i = %u/%u/%u, j = %u/%u/%u\n", i - j, j, obj_indices[i].normal_index, obj_indices[j].vertex_index, obj_indices[j].tex_coord_index, obj_indices[j].normal_index);
//                previous_index = j;
//                break;
//            }
//        }
//
//        if(previous_index > -1){
//            indices.push_back(indices[previous_index]);
//        }else{

            this->vertices.emplace_back(this->obj_vertices[this->obj_indices[i].vertex_index]);

    //        printf("before tex %u, tex_size:%d, obj_indices_size:%d\n", this->obj_indices[i].tex_coord_index, this->obj_tex_coords.size(), this->obj_indices.size());
            if(this->has_uvs){
    //            printf("tex #%d\tx: %f, y: %f, z: %f\n", i, this->obj_tex_coords[this->obj_indices[i].tex_coord_index].x, this->obj_tex_coords[this->obj_indices[i].tex_coord_index].y);
                this->tex_coords.emplace_back(this->obj_tex_coords[this->obj_indices[i].tex_coord_index]);
            }

            if(this->has_normals){
                this->normals.emplace_back(this->obj_normals[this->obj_indices[i].normal_index]);
            }

            this->indices.push_back(i);

//            current++;
//        }
//        }

    }
}

void Object::draw(shader& shader){

    shader.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indice_size, UNSIGNED_INT, 0);
}
