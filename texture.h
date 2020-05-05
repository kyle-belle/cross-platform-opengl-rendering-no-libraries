#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

class texture{

    public:

        unsigned int texture_id;
        const char* file_path;
        unsigned char* image;
        int width, height, bpp;

        int slot;

        texture(const char* path, int n_slot = 0);
        texture();
        ~texture();

        void load_texture(const char* path, int n_slot = 0);
        void delete_texture();
        void bind();
        void unbind();

        inline int get_width()const{ return width; }
        inline int get_height()const{ return height; }
        inline int get_bpp()const{ return bpp; }


};

#endif // TEXTURE_H_INCLUDED
