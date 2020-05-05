#ifndef LINUX_GL_WINDOW_H_INCLUDED
#define LINUX_GL_WINDOW_H_INCLUDED

#include "../../../Event/event.h"
#include "../../../Event/key_event.h"
#include "../../../Event/mouse_event.h"
#include <unordered_map>
#include <vector>
#include <X11/Xlib.h>
#include <GL/glx.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace std
{
	template <>
	struct hash<Event_type>
	{
		size_t operator()(const Event_type& v) const
		{
			return hash<int>()(static_cast<int>(v));
		}
	};
}

class gl_context{

    public:

        std::unordered_map< Event_type, std::vector<void(*)(Event*)>*, std::hash<Event_type> > event_handlers = {
            {Event_type::key_press, new std::vector<void(*)(Event*)>()},
            {Event_type::mouse_button_press, new std::vector<void(*)(Event*)>()},
            {Event_type::mouse_move, new std::vector<void(*)(Event*)>()},
            {Event_type::mouse_scroll, new std::vector<void(*)(Event*)>()}
        };
        int pixel_format;
        int gl_version_major;
        int gl_version_minor;
        int default_screen;
        bool running = true;
        bool window_created;
        Atom wm_delete;
        Display* display;
        Window root_window;
        Window gl_window;
        Colormap color_map;
        GLXFBConfig best_frame_buffer_config;
        XVisualInfo* best_visual_info;
        XSetWindowAttributes set_window_attribute;
        GLXContext render_context;
        XWindowAttributes window_attributes;
        XEvent event;


        int create_window(int width, int height, const char* window_name = "window");
        void init(int gl_version_major = 0, int gl_version_minor = 0, const char* wnd_class_name = "window class");

        void process_events();
        void swap_buffers();

        static gl_context* get_window_instance(){
            static gl_context c(true);

            return &c;
        }
        ~gl_context() {};

        void add_event_listener(Event_type et, void(*handler)(Event*));
        bool is_key_pressed(KeySym key);

        static gl_context* instance;
        gl_context(bool b){};
        gl_context(int gl_version_major = 0, int gl_version_minor = 0, const char* wnd_class_name = "window class");
    private:

};

#endif // LINUX_GL_WINDOW_H_INCLUDED
