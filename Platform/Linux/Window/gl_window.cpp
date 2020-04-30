#ifdef __linux__
#include "gl_window.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include "dirent.h"

int                   fb_attribs[] = {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,
      //GLX_SAMPLE_BUFFERS  , 1,
      //GLX_SAMPLES         , 4,
      None
     };

gl_context* gl_context::instance = nullptr;

gl_context::gl_context(int gl_version_maj, int gl_version_min, const char* wnd_class_name): gl_version_major(gl_version_maj), gl_version_minor(gl_version_min){
    // connect to X11 server
    printf("connecting to display server (X11 server).\n\n");
    display = XOpenDisplay(NULL);


    if(!display){
        printf("Error: cannot connect to display server (X11 server)\n\n");
        exit(0);
    }

    printf("grabbing default screen.\nscreen = monitor\n\n");
    default_screen = XDefaultScreen(display);

;
    //get root window
    root_window = XDefaultRootWindow(display);

    //get/set frame buffer config
    printf("getting frame buffer configs and selecting best one\n\n");
    int fb_count;
    GLXFBConfig* frame_buffer_config = glXChooseFBConfig(display, default_screen, fb_attribs, &fb_count);
    if(!frame_buffer_config){
        printf("Error: failed to get frame buffer configss\n\n");
        exit(1);
    }

    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    printf("%d frame buffer configs found.\n\n", fb_count);

    printf("___Visual Infos___\n");
    for(int i = 0; i < fb_count; i++){
        XVisualInfo* visual_info = glXGetVisualFromFBConfig(display, frame_buffer_config[i]);
        if(visual_info){
            int sample_buffers, samples;
            glXGetFBConfigAttrib(display, frame_buffer_config[i], GLX_SAMPLE_BUFFERS, &sample_buffers);
            glXGetFBConfigAttrib(display, frame_buffer_config[i], GLX_SAMPLES, &samples);
            printf("#%d. Visual ID: 0x%2lx\tSample Buffers: %d\tSamples: %d\n\n", i, visual_info->visualid, sample_buffers, samples);

            if((best_fbc < 0) || (sample_buffers && (samples > best_num_samp))){
                best_fbc = i, best_num_samp = samples;
            }
            if(worst_fbc < 0 || !sample_buffers || samples < worst_num_samp){
                worst_fbc = i, worst_num_samp = samples;
            }

        }
        XFree(visual_info);
    }

    printf("frame buffer config #%d determined to be best. get visual info for said config.\n\n", best_fbc);
    best_frame_buffer_config = frame_buffer_config[best_fbc];
    XFree(frame_buffer_config);
    //get visual info from frame buffer config
    best_visual_info = glXGetVisualFromFBConfig(display, best_frame_buffer_config);
    printf( "Chosen visual ID = 0x%lx\n\n", best_visual_info->visualid );

    printf("creating color map from root window\n\n");
    //create color map with root window
    color_map = XCreateColormap(display, root_window, best_visual_info->visual, AllocNone);

    //set window attributes
    set_window_attribute.colormap = color_map;
    set_window_attribute.event_mask = Expose | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;
}

void gl_context::init(int gl_version_maj, int gl_version_min, const char* wnd_class_name){

     gl_version_major = gl_version_maj;
     gl_version_minor = gl_version_min;
    // connect to X11 server
    printf("connecting to display server (X11 server).\n\n");
    display = XOpenDisplay(NULL);


    if(!display){
        printf("Error: cannot connect to display server (X11 server)\n\n");
        exit(0);
    }

    printf("grabbing default screen.\nscreen = monitor\n\n");
    default_screen = XDefaultScreen(display);

;
    //get root window
    root_window = XDefaultRootWindow(display);

    //get/set frame buffer config
    printf("getting frame buffer configs and selecting best one\n\n");
    int fb_count;
    GLXFBConfig* frame_buffer_config = glXChooseFBConfig(display, default_screen, fb_attribs, &fb_count);
    if(!frame_buffer_config){
        printf("Error: failed to get frame buffer configss\n\n");
        exit(1);
    }

    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    printf("%d frame buffer configs found.\n\n", fb_count);

    printf("___Visual Infos___\n");
    for(int i = 0; i < fb_count; i++){
        XVisualInfo* visual_info = glXGetVisualFromFBConfig(display, frame_buffer_config[i]);
        if(visual_info){
            int sample_buffers, samples;
            glXGetFBConfigAttrib(display, frame_buffer_config[i], GLX_SAMPLE_BUFFERS, &sample_buffers);
            glXGetFBConfigAttrib(display, frame_buffer_config[i], GLX_SAMPLES, &samples);
            printf("#%d. Visual ID: 0x%2lx\tSample Buffers: %d\tSamples: %d\n\n", i, visual_info->visualid, sample_buffers, samples);

            if((best_fbc < 0) || (sample_buffers && (samples > best_num_samp))){
                best_fbc = i, best_num_samp = samples;
            }
            if(worst_fbc < 0 || !sample_buffers || samples < worst_num_samp){
                worst_fbc = i, worst_num_samp = samples;
            }

        }
        XFree(visual_info);
    }

    printf("frame buffer config #%d determined to be best. get visual info for said config.\n\n", best_fbc);
    best_frame_buffer_config = frame_buffer_config[best_fbc];
    XFree(frame_buffer_config);
    //get visual info from frame buffer config
    best_visual_info = glXGetVisualFromFBConfig(display, best_frame_buffer_config);
    printf( "Chosen visual ID = 0x%lx\n\n", best_visual_info->visualid );

    printf("creating color map from root window\n\n");
    //create color map with root window
    color_map = XCreateColormap(display, root_window, best_visual_info->visual, AllocNone);

    //set window attributes
    set_window_attribute.colormap = color_map;
    set_window_attribute.event_mask = Expose | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask | FocusChangeMask;
}

int gl_context::create_window(int width, int height, const char* window_name){



    printf("CREATING WINDOW!!!\n\n");
    //create window
    gl_window = XCreateWindow(display, root_window, 0, 0, (unsigned int)width, (unsigned int)height, 0, best_visual_info->depth, InputOutput, best_visual_info->visual, CWColormap| CWEventMask, &set_window_attribute);

//    wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", True),
//    XSetWMProtocols(display, gl_window, &wm_delete, 1);
    //map created window to the display '
    XMapWindow(display, gl_window);

    //set name of window
    XStoreName(display, gl_window, window_name);

    //manually pull opengl function pointer
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );

    int context_attribs[] = {
                GLX_CONTEXT_MAJOR_VERSION_ARB, gl_version_major,
                GLX_CONTEXT_MINOR_VERSION_ARB, gl_version_minor,
                GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB
                ,0
              };

    render_context = glXCreateContextAttribsARB(display, best_frame_buffer_config, NULL, True, context_attribs);
    glXMakeCurrent(display, gl_window, render_context);
    return 0;
}

bool is_key_actually_released(Display& d, XEvent& e){
    if(e.type == KeyRelease && XEventsQueued(&d, QueuedAfterReading)){
        XEvent next;
        XPeekEvent(&d, &next);
        return !(next.type == KeyPress && next.xkey.time == e.xkey.time && next.xkey.keycode == e.xkey.keycode);
    }
    return true;
}

void gl_context::process_events(){

    XGetWindowAttributes(display, gl_window, &window_attributes);
    if(XCheckWindowEvent(display, gl_window, -1, &event)){
        char buf[128];
        KeySym k;
        switch(event.type){
            case KeyPress:{
                XLookupString(&event.xkey, buf, 128, &k, 0);
                if(true && strlen(buf) == 1){
                    buf[0] = toupper(buf[0]);
                    k = XStringToKeysym(buf);
                }
                Key_press_event e(k, false);
                printf("Key Press %c : %d\n", buf[0], k);
                std::vector<void(*)(Event*)> key_press_handlers = *event_handlers[Event_type::key_press];
                for(auto handler: key_press_handlers){
                    if(handler){
                        handler(&e);
                    }
                }
            }
            break;

            case KeyRelease:
                if(is_key_actually_released(*display, event)){
                    XLookupString(&event.xkey, buf, 128, &k, 0);
                    if(true && strlen(buf) == 1){
                        buf[0] = toupper(buf[0]);
                        k = XStringToKeysym(buf);
                    }
                    printf("Key released %c : %d\n", buf[0], event.xkey.keycode);
                }
            break;

            case MotionNotify:
                printf("Mouse Moved x: %.2f, y: %.2f\n", (float)event.xmotion.x/(float)window_attributes.width, (float)event.xmotion.y/(float)window_attributes.height);
            break;

            default:
                printf("unknown event type: %d\n", event.type);
            break;
        }
        glViewport(0, 0, window_attributes.width, window_attributes.height);
    }
}

bool gl_context::is_key_pressed(KeySym key){
    char keys[32];
    XQueryKeymap(display, keys);
    int keycode = XKeysymToKeycode(display, key);
    return !!(keys[keycode >> 3] & (1 << (keycode & 7)));
}

void gl_context::swap_buffers(){
    glXSwapBuffers(display, gl_window);
}

void gl_context::add_event_listener(Event_type et, void(*handler)(Event*)){
    std::vector<void(*)(Event*)>* handlers = event_handlers[et];
    handlers->push_back(handler);
}

#endif //__linux__
