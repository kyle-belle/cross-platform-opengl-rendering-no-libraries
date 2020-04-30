#ifndef GL_WINDOW_H_INCLUDED
#define GL_WINDOW_H_INCLUDED

#include "GL/glew.h"
#include <GL/gl.h>

#ifdef _WIN32
    #include "../Platform/Windows/Window/gl_window.h"
#endif // _WIN32

#ifdef __linux__
    #include "../Platform/Linux/Window/gl_window.h"
#endif // __linux__

#endif // GL_WINDOW_H_INCLUDED




#ifdef __WIN32__
#define main() WINAPI WinMain(HINSTANCE hins, HINSTANCE previous_inst, LPSTR args, int command_line)
    HINSTANCE hinst;
    #define gl_context_init() hinst = hins
#else
    #define gl_context_init()
#endif // __WIN32__
