#include "texture.h"
#include "stb_image.h"
#include "GL/glew.h"

   texture::texture(const char* path, int n_slot)
       : texture_id(0),  file_path(path), image(nullptr), height(0), width(0), bpp(0), slot(n_slot){

           stbi_set_flip_vertically_on_load(1);

           image = stbi_load(path, &width, &height, &bpp, 4);

           glGenTextures(1, &texture_id);
           glActiveTexture(GL_TEXTURE0 + slot);
           glBindTexture(GL_TEXTURE_2D, texture_id);

           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
           glGenerateMipmap(GL_TEXTURE_2D);
//           glBindTexture(GL_TEXTURE_2D, 0);

           if(image)
               stbi_image_free(image);

}

texture::texture(){}

void texture::load_texture(const char* path, int n_slot){
    file_path = path;
    slot = n_slot;
    stbi_set_flip_vertically_on_load(1);

    image = stbi_load(path, &width, &height, &bpp, 4);

    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, 0);

    if(image)
        stbi_image_free(image);
}

texture::~texture(){
//glDeleteTextures(1, &texture_id);
}

void texture::delete_texture(){
    glDeleteTextures(1, &texture_id);
}

void texture::bind(){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}


void texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}
