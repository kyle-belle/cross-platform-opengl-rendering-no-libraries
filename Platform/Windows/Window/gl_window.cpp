#ifdef _WIN32
#undef __WIN32__
#include "gl_window.h"
#include <stdio.h>
#include <stdlib.h>
#include "GL/glext.h"

LRESULT CALLBACK window_procedure(HWND handler,UINT msg,WPARAM wparam,LPARAM lparam){
    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_SIZE:{
            RECT win_size = {0};
            GetWindowRect(handler, &win_size)?printf("x: %d, y: %d\n", win_size.right - win_size.left, win_size.bottom - win_size.top):0;
            glViewport(0, 0, win_size.right - win_size.left, win_size.bottom - win_size.top);
        }
        break;

        default:
            return DefWindowProc(handler, msg, wparam, lparam);
    }

    return 0;
}

extern HINSTANCE hinst;

gl_context* gl_context::instance = nullptr;

gl_context::gl_context(int gl_version_maj, int gl_version_min, const char* wnd_class_name): gl_version_major(gl_version_maj), gl_version_minor(gl_version_min){

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;

    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.style = CS_DBLCLKS | CS_OWNDC;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = hinst;
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = wnd_class_name;
    window_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

}

void gl_context::init(int gl_version_maj, int gl_version_min, const char* wnd_class_name): {
    gl_version_major = gl_version_maj, gl_version_minor = gl_version_min;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;

    window_class.cbSize = sizeof(WNDCLASSEX);
    window_class.style = CS_DBLCLKS | CS_OWNDC;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = hinst;
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = wnd_class_name;
    window_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

}

int gl_context::create_window(int width, int height, const char* window_name){
    if(!RegisterClassEx(&window_class)){
        return -1;
    }

    window = CreateWindowEx(0, window_class.lpszClassName, window_name, WS_VISIBLE | WS_OVERLAPPEDWINDOW, 200, 200, width, height, NULL, NULL, window_class.hInstance, NULL);
    if(!window){
        int err = GetLastError();
        printf("%d", err);
        getchar();
        return -2;
    }

    device_context = GetDC(window);

    pixel_format = ChoosePixelFormat(device_context, &pfd);

    if(!SetPixelFormat(device_context, pixel_format, &pfd)){
        int err = GetLastError();
        printf("%d", err);
        getchar();
        return -3;
    }

    if(gl_version_major || gl_version_minor){

        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, gl_version_major,
            WGL_CONTEXT_MINOR_VERSION_ARB, gl_version_minor,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        HGLRC temp_rc = wglCreateContext(device_context);
        wglMakeCurrent(device_context, temp_rc);

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

        render_context = wglCreateContextAttribsARB(device_context, NULL, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(temp_rc);
        wglMakeCurrent(device_context, render_context);

    }else{

        render_context = wglCreateContext(device_context);
        wglMakeCurrent(device_context, render_context);
    }

    window_created = true;

    return 0;
}
#endif
