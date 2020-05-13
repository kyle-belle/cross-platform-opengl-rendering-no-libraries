#include "game_object.h"
#include <utility>

Game_object::Game_object(const char* obj_path): object(new Object(obj_path)), material(new Material(vector4f(1.f, 1.f, 1.f, 1.f))){}

Game_object::Game_object(const char* obj_path, Material& mat): object(new Object(obj_path)), material(new Material(mat)) {}

Game_object::Game_object(const char* obj_path, texture& tex): object(new Object(obj_path)), material(new Material(tex)) {}

Game_object::Game_object(const char* obj_path, vector4f color): object(new Object(obj_path)), material(new Material(color)) {}

Game_object::Game_object(Object&& obj): object(new Object(std::move(obj))), material(new Material(vector4f(1.f, 1.f, 1.f, 1.f))) {}

Game_object::Game_object(Object&& obj, Material& mat): object(new Object(std::move(obj))), material(new Material(mat)) {}

Game_object::Game_object(Object&& obj, texture& tex): object(new Object(std::move(obj))), material(new Material(tex)) {}

Game_object::Game_object(Object&& obj, vector4f color): object(new Object(std::move(obj))), material(new Material(color)) {}

Game_object::~Game_object(){
    delete this->object;
    delete this->material;
}

void Game_object::render(shader* Shader){
    if(this->object){
        Shader->set_material(*this->material);
        this->object->draw(*Shader);
    }
}
