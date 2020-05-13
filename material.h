#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "texture.h"
#include "vector4f.h"

class Material{

public:
    texture tex;
    vector4f colour;
    float specular;
    float shininess;

    Material(){}
    Material(Material& other);
    Material(Material&& other);
    Material(vector4f& Color);
    Material(vector4f&& Color);
    Material(texture& Texture);
    Material(texture& Texture, vector4f& Color);
    Material(texture& Texture, vector4f& Color, float Specular, float Shininess);
    Material(texture& Texture, vector4f&& Color, float Specular, float Shininess);

    void set_colour(vector4f& Color);
    void set_colour(vector4f&& Color);

    void set_material(texture& Texture);
    void set_material(texture& Texture, vector4f& Color);
    void set_material(texture& Texture, vector4f&& Color);

    void set_material(texture& Texture, vector4f& Colour, float Specular, float Shininess);
    void set_material(texture& Texture, vector4f&& Colour, float Specular, float Shininess);





};



#endif // MATERIAL_H_INCLUDED
