#ifndef WINDOWS_GL_WINDOW_H_INCLUDED
#define WINDOWS_GL_WINDOW_H_INCLUDED

#include "GL/wglew.h"
#include <windows.h>
#include <unordered_map>
#include <vector>

#include "../../../Event/event.h"
#include "../../../Event/key_event.h"
#include "../../../Event/mouse_event.h"

#define MAX_WINDOW_NAME_SIZE 64

class gl_context{

    public:

        std::unordered_map< Event_type, std::vector<void(*)(Event*)> > event_handlers;
        int pixel_format;
        int gl_version_major;
        int gl_version_minor;
        bool running = true;
        bool window_created = false;
        char window_name[MAX_WINDOW_NAME_SIZE];
        HWND window;
        HDC device_context;
        HGLRC render_context;
        PIXELFORMATDESCRIPTOR pfd;
        WNDCLASSEX window_class = {0};
        MSG msg = {0};

        ~gl_context() = default;

        int create_window(int width, int height, const char* window_name = "window");

        void init(int gl_version_major = 0, int gl_version_minor = 0, const char* wnd_class_name = "window class");

        void set_window_name(const char* name);
        void set_temp_window_name(const char* name);

        void add_event_listener(Event_type et, void(*)(Event*));
        bool is_key_pressed(int key);
        void set_vysnc(bool b);

        void process_events();
        void swap_buffers();
        static gl_context* instance;
        static gl_context* get_window_instance(){
            if(!gl_context::instance){
                gl_context::instance = new gl_context();
            }

            return gl_context::instance;
        }
    private:

        gl_context(int gl_version_major = 0, int gl_version_minor = 0, const char* wnd_class_name = "window class");
};

#endif // WINDOWS_GL_WINDOW_H_INCLUDED
