#include "material.h"



Material::Material(vector4f& Color): colour(Color), specular(1.f), shininess(32) {}
Material::Material(vector4f&& Color): colour(Color), specular(1.f), shininess(32) {}

Material::Material(texture& Texture):tex(Texture), colour(vector4f(1.f, 1.f, 1.f, 1.f)) {}

Material::Material(texture& Texture, vector4f& Color):tex(Texture), colour(Color), specular(1.f), shininess(32) {}


Material::Material(texture& Texture, vector4f& Color, float Specular, float Shininess): tex(Texture), colour(Color), specular(Specular), shininess(Shininess){}
Material::Material(texture& Texture, vector4f&& Color, float Specular, float Shininess): tex(Texture), colour(Color), specular(Specular), shininess(Shininess){}

Material::Material(Material& other): tex(other.tex), colour(other.colour), specular(other.specular), shininess(other.shininess) {}

Material::Material(Material&& other): tex(other.tex), colour(other.colour), specular(other.specular), shininess(other.shininess) {}

void Material::set_colour(vector4f& Color){
    this->colour = Color;
}

void Material::set_colour(vector4f&& Color){
    this->colour = Color;
}

void Material::set_material(texture& Texture){
    this->tex = Texture;
    this->colour = vector4f(1.0f,1.0f,1.0f,1.0f);
    this->specular = 1;
    this->shininess = 32;
}

void Material::set_material(texture& Texture, vector4f& Color){
    this->tex = Texture;
    this->colour = Color;
    this->specular = 1;
    this->shininess = 32;
}

void Material::set_material(texture& Texture, vector4f&& Color){
    this->tex = Texture;
    this->colour = Color;
    this->specular = 1;
    this->shininess = 32;
}

void Material::set_material(texture& Texture, vector4f& Color, float Specular, float Shininess){
    this->tex = Texture;
    this->colour = Color;
    this->specular = Specular;
    this->shininess = Shininess;
}

void Material::set_material(texture& Texture, vector4f&& Color, float Specular, float Shininess){
    this->tex = Texture;
    this->colour = Color;
    this->specular = Specular;
    this->shininess = Shininess;
}







