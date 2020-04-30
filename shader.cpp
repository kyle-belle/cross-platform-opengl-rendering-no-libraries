#include <stdio.h>
#include <string.h>
#include <iostream>
#include "shader.h"
#include "GL/glew.h"

    shader::shader(const char* vertex_shader, const char* fragment_shader){
        int compile;

        id = glCreateProgram();

        unsigned int vertex_shader_program = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragment_shader_program = glCreateShader(GL_FRAGMENT_SHADER);

        int shader_length = strlen(vertex_shader);
        glShaderSource(vertex_shader_program, 1, &vertex_shader, &shader_length);
        shader_length = strlen(fragment_shader);
        glShaderSource(fragment_shader_program, 1, &fragment_shader, &shader_length);

        glCompileShader(vertex_shader_program);

        glGetShaderiv(vertex_shader_program, GL_COMPILE_STATUS, &compile);

        if(!compile){
            int length;
            glGetShaderiv(vertex_shader_program, GL_INFO_LOG_LENGTH, &length);
            char err_msg[length];
            glGetShaderInfoLog(vertex_shader_program, length, &length, err_msg);

            printf("Failed to compile vertex shader with error: %s", err_msg);

            getchar();
            exit(-1);
        }

        glCompileShader(fragment_shader_program);

        glGetShaderiv(fragment_shader_program, GL_COMPILE_STATUS, &compile);

        if(!compile){
            int length;
            glGetShaderiv(fragment_shader_program, GL_INFO_LOG_LENGTH, &length);
            char err_msg[length];
            glGetShaderInfoLog(fragment_shader_program, length, &length, err_msg);

            printf("Failed to compile fragment shader with error: %s", err_msg);

            getchar();
            exit(-1);
        }

        glAttachShader(id, vertex_shader_program);
        glAttachShader(id, fragment_shader_program);
        glLinkProgram(id);
        glValidateProgram(id);
        glDeleteShader(vertex_shader_program);
        glDeleteShader(fragment_shader_program);
    }

    void shader::set_uniform_i(const char* name, int value){
        glUniform1i(glGetUniformLocation(id, name), value);
    }

    void shader::set_uniform_4i(const char* name, int value1, int value2, int value3, int value4){
        glUniform4i(glGetUniformLocation(id, name), value1, value2, value3, value4);
    }

    void shader::set_uniform_f(const char* name, float value){
        glUniform1f(glGetUniformLocation(id, name), value);
    }

    void shader::set_uniform_4f(const char* name, float value1, float value2, float value3, float value4){
        glUniform4f(glGetUniformLocation(id, name), value1, value2, value3, value4);
    }

    void shader::set_uniform_3f(const char* name, float value1, float value2, float value3){
        glUniform3f(glGetUniformLocation(id, name), value1, value2, value3);
    }

    void shader::set_uniform_2f(const char* name, float value1, float value2){
        glUniform2f(glGetUniformLocation(id, name), value1, value2);
    }

    void shader::set_uniform_matrix4(const char* name, matrix4x4& mat4){
        glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, &mat4.m[0][0]);
    }

    void shader::bind(){
        glUseProgram(id);
    }

    void shader::unbind(){
        glUseProgram(0);
    }
