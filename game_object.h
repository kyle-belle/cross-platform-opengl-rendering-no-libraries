#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED


#include "object.h"
#include "material.h"
#include "transform.h"
#include "vector4f.h"

class Game_object{
    public:
        Object* object;
        Material* material;
        transformation transform;
        // Maybe store a Shader pointer here as well

        Game_object(){}
        Game_object(const char* obj_path);
        Game_object(const char* obj_path, Material& mat);
        Game_object(const char* obj_path, texture& tex);
        Game_object(const char* obj_path, vector4f color);
        Game_object(Object&& obj);
        Game_object(Object&& obj, Material& mat);
        Game_object(Object&& obj, texture& tex);
        Game_object(Object&& obj, vector4f color);
        ~Game_object();

        void render(shader* Shader);
};

#endif // GAME_OBJECT_H_INCLUDED
