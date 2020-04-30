#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include "matrices.h"

class shader{

    public:

        unsigned int handle;
        unsigned int& id = handle;

        shader() = default;
        shader(const char* vertex_shader, const char* fragment_shader);
        ~shader() = default;

        void set_uniform_i(const char* name, int value);
        void set_uniform_4i(const char* name, int value1, int value2, int value3, int value4);

        void set_uniform_f(const char* name, float value);
        void set_uniform_4f(const char* name, float value1, float value2, float value3, float value4);
        void set_uniform_3f(const char* name, float v1, float v2,float v3);
        void set_uniform_2f(const char* name, float v1, float v2);

        void set_uniform_matrix4(const char* name, matrix4x4& mat4);

        void bind();

        #define use() bind()

        void unbind();


};

#endif // SHADER_H_INCLUDED
