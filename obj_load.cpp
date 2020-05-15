#include "obj_load.h"
#include "object.h"
#include "utils.h"

#define FACE_PARSER_TOKEN 'f'
#define VERTEX_PARSER_TOKEN 'v'
#define FACE_VALUE_SEPERATOR_TOKEN '/'
#define VERTEX_NORMAL_PARSER_TOKEN 'n'
#define VERTEX_POSITION_PARSER_TOKEN ' '
#define VERTEX_TEXCOORD_PARSER_TOKEN 't'

class obj_parse_helper{
    public:

        char face_line[128];
        char face_value[64];
        char face_vert[4][16];
        char face_uv[4][16];
        char face_norm[4][16];

        Model_index temp_obj_index;

        //bool has_uvs = false, has_normals = false;

        unsigned int start_line_index;
        unsigned int start_value_index;

        unsigned int end_line_index;
        unsigned int end_value_index;

        unsigned int line_seperator;
        unsigned int value_seperator;


        void parse_face_value(unsigned int index, bool& has_uvs, bool& has_normals){
            unsigned int i;
            for(i = start_value_index; i <= end_value_index; i++){

                if(face_value[i] == FACE_VALUE_SEPERATOR_TOKEN || i == end_value_index){
//
                    value_seperator = i - start_value_index;
                    memcpy(face_vert[index], &face_value[start_value_index], value_seperator);
                    face_vert[index][value_seperator] = '\0';

                    temp_obj_index.vertex_index = (atoi(face_vert[index]) - 1);

                    if(face_value[i] == FACE_VALUE_SEPERATOR_TOKEN){
                        if(face_value[i+1] == FACE_VALUE_SEPERATOR_TOKEN){
                            has_normals = true;
//                            ++value_seperator;
                            break;
                        }
                        has_uvs = true;
//                        printf("has uvs\n");
                    }
//                    if((*(int*)&temp_obj_index.vertex_index) == -1){ // purely debuging purposes
//                        printf("face_vert: %d\n", atoi(face_vert[index]));
//                    }
                    break;
                }
            }

            start_value_index += value_seperator + 1;
////////////////////////////////////////////////////////
            if(has_uvs){

                for(i = start_value_index; i <= end_value_index; i++){
                    if(face_value[i] == FACE_VALUE_SEPERATOR_TOKEN || i == end_value_index){
//                                    printf("uv i: %d\n", i);

                        if(face_value[i] == FACE_VALUE_SEPERATOR_TOKEN){
                            has_normals = true;
                            if(i == start_value_index){
                                value_seperator = 0;
                                break;
                            }
//                            printf("has normals\n");
                        }

                        value_seperator = i - start_value_index;
                        memcpy(face_uv[index], &face_value[start_value_index], value_seperator);
                        face_uv[index][value_seperator] = '\0';

                        temp_obj_index.tex_coord_index = (atoi(face_uv[index]) - 1);

//                      if((*(int*)&temp_obj_index.tex_coord_index) == -1){ // purely debuging purposes
//                        printf("face_uv: %d\n", atoi(face_uv[index]));
//                      }
                        break;
                    }
                }
            }

            start_value_index += value_seperator + 1;
///////////////////////////////////////////////////////////////
            if(has_normals){

                for(i = start_value_index; i <= end_value_index; i++){

                    if(i == (end_value_index)){
//                        printf("norm i: %d\n", i);
                        value_seperator = i - start_value_index;
                        memcpy(face_norm[index], &face_value[start_value_index], value_seperator);
                        face_norm[index][value_seperator] = '\0';

                        temp_obj_index.normal_index = (atoi(face_norm[index]) - 1);

//                        if((*(int*)&temp_obj_index.normal_index) == -1){ // purely debuging purposes
//                            printf("face_norm: %d, %s\n", temp_obj_index.normal_index, face_norm[index]);
//                        }
                        break;
                    }
                }
            }
        }

        void parse_face(const char* face, unsigned int face_length, std::vector<Model_index>& model_indices, bool& has_uvs, bool& has_normals){
            unsigned int i;
            start_value_index = 0;
            start_line_index = 0;
//            end_line_index = face_length;

            for(i = start_line_index; i <= face_length; i++){
                if(face[i] == ' '){
                    end_line_index = i;
                    break;
                }
                end_line_index = i;
            }

            if(end_line_index < face_length){

                end_value_index = end_line_index - start_line_index;
                //printf("end - start: %d\n", end_ - start);
                memcpy(face_value, &face[start_line_index], end_value_index);
                face_value[end_value_index] = '\0';
                //printf("\nface_value: %s\n", face_value);

                parse_face_value(0, has_uvs, has_normals);

                model_indices.emplace_back(temp_obj_index);
            }else{
                exit(1);
            }


/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
                start_line_index = end_line_index + 1;
                start_value_index = 0;
                for(i = start_line_index; i <= face_length; i++){
                    if(face[i] == ' '){
                        end_line_index = i;
                        break;
                    }
                    end_line_index = i;
                }

                if(end_line_index < face_length){
                    end_value_index = end_line_index - start_line_index;
                    //printf("end - start: %d\n", end - start);
                    memcpy(face_value, &face[start_line_index], end_value_index);
                    face_value[end_value_index] = '\0';
                    //printf("\nface_value: %s\n", face_value);

                    parse_face_value(1, has_uvs, has_normals);

                    model_indices.emplace_back(temp_obj_index);
                }else{
                    exit(2);
                }
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////
                start_line_index = end_line_index + 1;
                start_value_index = 0;

                for(i = start_line_index; i <= face_length; i++){
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

                    parse_face_value(2, has_uvs, has_normals);

                    model_indices.emplace_back(temp_obj_index);
                }else{
                    exit(3);
                }

/// ////////////////////////////////////////////////////////////////////////////

                if(end_line_index < face_length){
                    temp_obj_index.vertex_index = ((atoi(face_vert[0])) - 1);

                    if(has_uvs){
                        temp_obj_index.tex_coord_index = atoi(face_uv[0]) - 1;
                    }

                    if(has_normals){
                        temp_obj_index.normal_index = atoi(face_norm[0]) - 1;
                    }

                    model_indices.emplace_back(temp_obj_index);

                    temp_obj_index.vertex_index = ((atoi(face_vert[2])) - 1);
                    if(has_uvs){
                        temp_obj_index.tex_coord_index = atoi(face_uv[2]) - 1;
                    }

                    if(has_normals){
                        temp_obj_index.normal_index = atoi(face_norm[2]) - 1;
                    }

                    model_indices.emplace_back(temp_obj_index);

                    start_line_index = end_line_index + 1;
                    start_value_index = 0;

                    for(i = start_line_index; i <= face_length; i++){
                        if(face[i] == ' '){
                            end_line_index = i;
                            break;
                        }
                        end_line_index = i;
                    }

                    if(end_line_index <= face_length){
                        end_value_index = end_line_index - start_line_index;
//                        printf("end - start: %d\n", end_value_index);
                        memcpy(face_value, &face[start_line_index], end_value_index);
                        face_value[end_value_index] = '\0';
                        //printf("\nface_value: %s\n", face_value);

                        parse_face_value(3, has_uvs, has_normals);

                        model_indices.emplace_back(temp_obj_index);
                    }
                }
        }



};

OBJ_loader::OBJ_loader(const char* file): Model_loader(file){
    this->load(this->filepath);
}

OBJ_loader::OBJ_loader(const char* file, Object* object): Model_loader(file){
    this->load(this->filepath);

    if(!object){ //maybe i should return early if a null object is passed but for now i'll create a new one.
        object = new Object();
    }

    object->has_uvs = this->has_uvs;
    object->has_normals = this->has_normals;

    object->create_object(this->model_vertices, this->model_tex_coords, this->model_normals, this->model_indices);
    //TODO: Load obj data into buffers
}

int OBJ_loader::load(const char* file) {
    FILE* obj_file;
    obj_parse_helper face_parser;
//    unsigned int i=0;//, start, end, seperator; // , j,k;
    char token;
    char face[128];
    unsigned int index_length;

    vector3f vert;
    vector3f norm;
    vector2f tex_;

    obj_file = fopen(file, "r");

    if(obj_file){
        // TODO: load OBJ

        while(!feof(obj_file)){

            token = fgetc(obj_file);

            switch(token){

                case VERTEX_PARSER_TOKEN:

                    switch(fgetc(obj_file)){

                        case VERTEX_POSITION_PARSER_TOKEN:
                            fscanf(obj_file, "%f %f %f", &vert.x, &vert.y, &vert.z);
//                            printf("Vs1 %f, %f, %f\n", vert.x, vert.y, vert.z);
                            this->model_vertices.emplace_back(vector3f(vert.x, vert.y, vert.z));
//                            printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        case VERTEX_NORMAL_PARSER_TOKEN:
                            fscanf(obj_file, "%f %f %f", &norm.x, &norm.y, &norm.z);
                            this->model_normals.emplace_back(vector3f(norm.x, norm.y, norm.z));
                            //printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        case VERTEX_TEXCOORD_PARSER_TOKEN:
                            fscanf(obj_file, "%f %f", &tex_.x, &tex_.y);
                            this->model_tex_coords.emplace_back(vector2f(tex_.x, tex_.y));
                            //printf("fuck you: %c", fgetc(obj_file));
                            fgetc(obj_file);
                        break;

                        default:
                            printf("something not right\n");
                            exit(1);

                    }
                break;

                case FACE_PARSER_TOKEN:
                    fgetc(obj_file);
                    fscanf(obj_file, "%[^\n]s", face);
    //                fflush(obj_file);

                    r_trim(r_trim(r_trim(face, '\r'), '\n'));
                    index_length = strlen(face);

                    face_parser.parse_face(/*r_trim(*/face/*)*/, index_length, this->model_indices, this->has_uvs, this->has_normals);
                    fgetc(obj_file);

                break;

                default:
                    fgets(face, 127, obj_file);
//                    printf("fgets(face, 25, obj_file): %s\n", fgets(face, 62, obj_file));

                }
            }
            fclose(obj_file);
        }else{
            printf("could not load file %s", file);
        }
        return 0;
}
