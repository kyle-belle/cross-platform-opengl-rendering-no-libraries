#include "GL/glew.h"
#include "Window/gl_window.h"
#if defined __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#endif
//#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <chrono>
//#include <array>
#include "obj_loader.h"
#include "object.h"
#include "shaders.h"
#include "shader.h"
#include "transform.h"
#include "texture.h"
#include "stb_image.h"
#include "keyboard.h"
#include "utils.h"
#include "TIMER.H"
#include "utils.h"
#include "game_object.h"

//using namespace std;
float transformation::zNEAR = 0.1f;
float transformation::zFAR = 1000.0f;
float transformation::FOV = 35.0f;
int transformation::HEIGHT;
int transformation::WIDTH;

camera transformation::Camera;

// main (kinda)
//int WINAPI WinMain(HINSTANCE hinst, HINSTANCE previous_inst, LPSTR args, int command_line){

std::chrono::duration<double, std::milli> TIME::time;
std::chrono::duration<double, std::milli> TIME::delta;
std::chrono::duration<double, std::milli> TIME::last_tick;

int main(){

//    __asm__("movl %edx, %eax\n\t"
//            "addl $2, %eax\n\t");

//    char a1[] = "      kacdajajsadd";
//    char a2[] = "      k acdajajsadd               ";
//    char a3[] = "      k acdajajsa d   d";
//    char a4[] = "kacd ajajsadd     ";
//    char a5[] = "k acdaj ajsad d";
//
//    printf("original: %s, trim: %s, r_trim: %s, l_trim: %s\n\n", a1, trim(a1), r_trim(a1), l_trim(a1));
//    printf("original: %s, trim: %s, r_trim: %s, l_trim: %s\n\n", a2, trim(a2), r_trim(a2), l_trim(a2));
//    printf("original: %s, trim: %s, r_trim: %s, l_trim: %s\n\n", a3, trim(a3), r_trim(a3), l_trim(a3));
//    printf("original: %s, trim: %s, r_trim: %s, l_trim: %s\n\n", a4, trim(a4), r_trim(a4), l_trim(a4));
//    printf("original: %s, trim: %s, r_trim: %s, l_trim: %s\n\n", a5, trim(a5), r_trim(a5), l_trim(a5));

    printf("Hello world!\n");
    gl_context_init();
    gl_context* context = gl_context::get_window_instance();
    context->init(3,3);

    context->create_window(640, 480, "bootleg roblox");

    // using experimental opengl because some GPUs dont natively(in non-experimental mode) support the modern opengl functions
    glewExperimental = GL_TRUE;
    if(glewInit()!= GLEW_OK){ //initializing glew library
        printf("error");
    }



    printf("opengl version %s\n", glGetString(GL_VERSION));

    // Triangle vertices
//    float vertices[24] = {  -0.5f, -0.5f,  0.5f,
//                             0.5f, -0.5f,  0.5f,
//                             0.5f,  0.5f,  0.5f,
//                            -0.5f,  0.5f,  0.5f,
//                            // back
//                            -0.5f, -0.5f, -0.5f,
//                             0.5f, -0.5f, -0.5f,
//                             0.5f,  0.5f, -0.5f,
//                            -0.5f,  0.5f, -0.5f };

//    float tex_coords[48] = { 0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f,
//                             0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f,
//                             0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f,
//                             0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f,
//                             0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f,
//                             0.0f, 0.0f,
//                             1.0f, 0.0f,
//                             1.0f, 1.0f,
//                             0.0f, 1.0f  };

//    unsigned int indices[36] = { // front
//                                    0, 1, 2,
//                                    2, 3, 0,
//                                    // right
//                                    1, 5, 6,
//                                    6, 2, 1,
//                                    // back
//                                    7, 6, 5,
//                                    5, 4, 7,
//                                    // left
//                                    4, 0, 3,
//                                    3, 7, 4,
//                                    // bottom
//                                    4, 5, 1,
//                                    1, 0, 4,
//                                    // top
//                                    3, 2, 6,
//                                    6, 7, 3 };
//
//    printf("%d\n", sizeof(indices));

//    unsigned int VAO;
//    unsigned int VBO;
//    unsigned int IBO;
//    unsigned int TBO;

//    Object cube(vertices, sizeof(vertices), tex_coords, sizeof(tex_coords), indices, sizeof(indices));

//    Sleep(2000);

//    QueryPerformanceCounter()
//
//    std::chrono::high_resolution_clock::time_point point = std::chrono::high_resolution_clock::now();
    clock_t start, end;
    start = clock();
    printf("started my obj loader: %ld\n", start);


    Game_object game_object(Object("Handgun.obj"), vector4f(1.f, 1.f, 1.f, 1.f));
    Object my_monkey2("Handgun.obj");
    Object my_lamborghiniaventador("Handgun.obj");
    Object my_monkey4("Handgun.obj");
    Object my_monkey5("Handgun.obj");
    Object my_monkey6("Handgun.obj");
    Object my_monkey7("Handgun.obj");
    Object my_monkey8("Handgun.obj");
    Object my_monkey9("Handgun.obj");
    Object my_monkey10("Handgun.obj");

    end = clock();
    printf("ended my obj loader: %ld\n", end);

    printf("total time to complete 10 of my obj loader: %.2fsec\n", (double)(end - start)/CLOCKS_PER_SEC);

    start = clock();
    printf("started his obj loader: %ld\n", start);

    IndexedModel his_monkey = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey2 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_lamborghiniaventador = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey4 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey5 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey6 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey7 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey8 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey9 = OBJModel("Handgun.obj").ToIndexedModel();
    IndexedModel his_monkey10 = OBJModel("Handgun.obj").ToIndexedModel();

    end = clock();
    printf("ended his obj loader: %ld\n", end);

    printf("total time to complete 10 of his obj loader: %.2fsec\n", (double)(end - start)/CLOCKS_PER_SEC);

//    my_monkey.buffer_data(his_monkey);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);

//    if(my_monkey.indices.size() != his_monkey.indices.size()){
//        printf("different size indices: mine(%lu), his(%lu)\n", my_monkey.indices.size(), his_monkey.indices.size());
//    }
//    if(my_monkey.vertices.size() != his_monkey.positions.size()){
//        printf("different size vertices: mine(%lu), his(%lu)\n", my_monkey.vertices.size(), his_monkey.positions.size());
//    }
//    if(my_monkey.tex_coords.size() != his_monkey.texCoords.size()){
//        printf("different size tex_coords: mine(%lu), his(%lu)\n", my_monkey.tex_coords.size(), his_monkey.texCoords.size());
//    }
//    if(my_monkey.normals.size() != his_monkey.normals.size()){
//        printf("different size normals: mine(%lu), his(%lu)\n", my_monkey.normals.size(), his_monkey.normals.size());
//    }

    // creating and binding a vertex array Object
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    //unsigned int VBO;
//    // creating and binding a vertex buffer Object(VBO)
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // specifying the attributes(details) of the vertex buffer Object(VBO) we just binded (must be bound) also enabling it
//    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // creating and binding a index buffer Object(IBO)
//    glGenBuffers(1, &IBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    //generating texture-coordinates buffer Object(TBO)
//    glGenBuffers(1, &TBO);
//    glBindBuffer(GL_ARRAY_BUFFER, TBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(2, 2, GL_FLOAT, false, 2*sizeof(float), (void*)0);
//    glEnableVertexAttribArray(2);

    /// setting texture attributes

    // creating a texture Object (texture)
    texture texture1("handgun_C.jpg", 0);
    texture1.bind();
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    // setting texture wrapping
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//
//    // setting border colour
//    float border_colour[4] = {0.0f, 0.0f, 0.0f, 0.0f};
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_colour);
//
//    // setting filter options min/mag
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    // loading image
//    stbi_set_flip_vertically_on_load(true);
//    int width, height, channels;
//    unsigned char* image = stbi_load("sun2.jpg", &width, &height, &channels, 4);
//
//    if(image){
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        printf("failed to load image requested!!");
//    }
    texture texture2("bootleg.jpg", 1);
    texture2.bind();
//    unsigned int texture_2;
//    glGenTextures(1, &texture_2);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture_2);
//
//    // setting texture wrapping
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//
//    // setting border colour
////    float border_colour[4] = {0.0f, 0.0f, 0.0f, 0.0f};
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_colour);
//
//    // setting filter options min/mag
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    // loading image
//    //stbi_set_flip_vertically_on_load(true);
////    int width, height, channels;
//    image = stbi_load("bootleg.jpg", &width, &height, &channels, 4);
//
//    if(image){
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }else{
//        printf("failed to load image requested!!");
//    }
//
//    stbi_image_free(image);

    shader light_object_shader(vertex_shader, light_fragment_shader);
    light_object_shader.use();
    light_object_shader.set_uniform_4f("light_color", 1.f, 1.f, 1.f, 1.f);
    shader basic_shader(vertex_shader, fragment_shader);
    basic_shader.use();
    //glViewport(0, 0, 640, 480);

    glEnable(GL_DEPTH_TEST);

    basic_shader.set_uniform_i("texel", 0);
    basic_shader.set_uniform_i("texel_2", 1);

    camera cam(vector3f(0.0f, 0.0f, -1.5f));

    transformation transform;
    transform.set_camera(cam);
    transform.set_projection(70.0f, 480, 640, 0.1f, 1000.0f);
    matrix4x4 proj = transform.get_projected_transformation();
    basic_shader.set_uniform_matrix4("u_mvp", proj);

//    int rand_color = glGetUniformLocation(shader_program, "rand_color");


    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %d\n", err);
    }

    glClearColor(0, 0, 0, 0);

//    context->add_event_listener(Event_type::key_press, [](Event* event){/*printf("Key Press Callback\n");*/
//        Key_press_event* key_event = (Key_press_event*)event;
//        printf("%d key code in callback\n", key_event->key_code);
//        switch(key_event->key_code){
//            case KEY_A:
//                transformation::Camera.move(transformation::Camera.get_left(), 0.05f);
//            break;
//
//            case KEY_D:
//                transformation::Camera.move(transformation::Camera.get_right(), 0.05f);
//            break;
//
//            case KEY_S:
//                transformation::Camera.move(transformation::Camera.get_forward(), -0.05f);
//            break;
//
//            case KEY_W:
//                transformation::Camera.move(transformation::Camera.get_forward(), 0.05f);
//            break;
//
//            default:
//                return;
//        }
//    });


    TIME::time = std::chrono::high_resolution_clock::now().time_since_epoch();
    if(is_extension_supported("GLX_MESA_swap_control")){
        printf("GLX_SGI_swap_control is supported\n");
    }else{
        printf("GLX_SGI_swap_control is not supported\n");
        printf("%s\n", glXQueryExtensionsString(context->display, context->default_screen));
    }

    context->set_vysnc(false);

    float random_counter = 0;
    int frames = 0;
    char temp_window_name[MAX_WINDOW_NAME_SIZE];
    float temp = 0.00f;

    basic_shader.set_uniform_f("ambient_light", 0.3f);

    while(context->running){
        TIME::last_tick = TIME::time;
        TIME::time = std::chrono::high_resolution_clock::now().time_since_epoch();
        TIME::delta = TIME::time - TIME::last_tick;
        random_counter += TIME::delta.count();
        ++frames;
        if(random_counter >= 1000.0f){
            snprintf(temp_window_name, MAX_WINDOW_NAME_SIZE-1, "%s - %f FPS", context->window_name, frames/(random_counter/1000));
            context->set_temp_window_name(temp_window_name);
            random_counter = 0;
            frames = 0;
        }
//        printf("frame took %fms\n", TIME::delta.count());

        context->process_events();

        if(context->is_key_pressed(KEY_A)){
            transformation::Camera.move(transformation::Camera.get_left(), 10.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_D)){
            transformation::Camera.move(transformation::Camera.get_right(), 10.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_S)){
            transformation::Camera.move(transformation::Camera.get_forward(), -10.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_W)){
            transformation::Camera.move(transformation::Camera.get_forward(), 10.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_ARROW_UP)){
            transformation::Camera.rotate_x(-100.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_ARROW_DOWN)){
            transformation::Camera.rotate_x(100.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_ARROW_LEFT)){
            transformation::Camera.rotate_y(-100.0f * (TIME::delta.count()/1000));
        }

        if(context->is_key_pressed(KEY_ARROW_RIGHT)){
            transformation::Camera.rotate_y(100.0f * (TIME::delta.count()/1000));
        }

        transform.set_translation(2*sin(TIME::time.count()/1000), 2, 2*cos(TIME::time.count()/1000));
        transform.set_rotation(0,90,0);
        transform.set_scale(0.5f, 0.5f, 0.5f);
        matrix4x4 proj = transform.get_projected_transformation();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light_object_shader.use();
        light_object_shader.set_uniform_matrix4("u_mvp", proj);
        game_object.render(&light_object_shader);
//        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, 0);

        transform.set_translation(0, 0, 0);
        transform.set_rotation(0,180,0);
        transform.set_scale(1.0f, 1.0f, 1.0f);
        transform.get_projected_transformation();
        proj = transform.get_projected_transformation();
        matrix4x4 translation = transform.get_transformation();

        basic_shader.use();
//        basic_shader.set_uniform_4f("rand_color", (float)(rand() % 255 + 1)/255, (float)(rand() % 255 + 1)/255, (float)(rand() % 255 + 1)/255, 1.0f);
        basic_shader.set_uniform_4f("light_color", 1.f, 1.f, 1.f, 1.f);
        basic_shader.set_uniform_4f("object_color", 1.f, 0.5f, 1.f, 1.f);
        basic_shader.set_uniform_matrix4("model", translation);
        basic_shader.set_uniform_3f("light_pos", 2*sin(TIME::time.count()/1000), 2, 2*cos(TIME::time.count()/1000));
        basic_shader.set_uniform_3f("eye_pos", transform.Camera.position.x, transform.Camera.position.y, transform.Camera.position.z);
        basic_shader.set_uniform_matrix4("u_mvp", proj);
        game_object.render(&basic_shader);
//        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, 0);
        temp+=0.01f;
        context->swap_buffers();
    }

    return 0;
}
