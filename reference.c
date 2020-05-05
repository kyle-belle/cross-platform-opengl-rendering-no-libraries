////window procedure event handler
//LRESULT CALLBACK window_procedure(HWND handler,UINT msg,WPARAM wparam,LPARAM lparam){
//    switch(msg){
//        case WM_DESTROY:
//            PostQuitMessage(0);
//            break;
//
//        default:
//            return DefWindowProc(handler, msg, wparam, lparam);
//    }
//
//    return 0;
//}


// main (kinda)
//int WINAPI WinMain(HINSTANCE hinst, HINSTANCE previous_inst, LPSTR args, int command_line){

//    HWND main_window_handle;
//    MSG msg = {0};
//    HDC device_context;
//    HGLRC opengl_render_context;
//    PIXELFORMATDESCRIPTOR pfd;

    //setting up window class
//    WNDCLASSEX window_class = {0};
//
//    window_class.cbSize = sizeof(WNDCLASSEX);
//    window_class.style = CS_DBLCLKS || CS_OWNDC;
//    window_class.lpfnWndProc = window_procedure;
//    window_class.hInstance = hinst;
//    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
//    window_class.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
//    window_class.lpszMenuName = NULL;
//    window_class.lpszClassName = "bootleg roblox";
//    window_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // registering the window class
//    if(!RegisterClassEx(&window_class)){
//        return -1;
//    }

    // creating the window
//    main_window_handle = CreateWindowEx(NULL, window_class.lpszClassName, "bootleg roblox", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 200, 200, 640, 480, NULL, NULL, hinst, NULL);

    // retrieving the device context of the window
//    device_context = GetDC(main_window_handle);

    //setting up the pixel format for the device context
    //PIXELFORMATDESCRIPTOR pfd;
//    pfd.nSize = sizeof(PIXELFORMATDESCRIPT OR);
//    pfd.nVersion = 1;
//    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.cColorBits = 32;
//    pfd.cDepthBits = 24;


    // retrieving a number which represents the pixel format we described earlier
//    int pixel_format = ChoosePixelFormat(device_context, &pfd);
//
//    // setting the pixel format of the window with the given device context
//    if(!SetPixelFormat(device_context, pixel_format, &pfd)){
//        GetLastError();
//        //std::cin.get();
//        return -2;
//    }

    //HGLRC opengl_render_context;
    // creating an opengl context for this window
//    HGLRC temp_rc = wglCreateContext(device_context);

    // making the context current
//    wglMakeCurrent(device_context, temp_rc);

    // using experimental opengl because some GPUs dont natively(or rather in non-experimental mode) support the modern opengl functions
    glewExperimental = GL_TRUE;
    if(glewInit()!= GLEW_OK){ //initializing glew library
        printf("error");
    }



//    int attribs[] = {
//        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
//        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
//        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
//        NULL
//    };

//    opengl_render_context = wglCreateContextAttribsARB(device_context, NULL, attribs);
//    wglMakeCurrent(NULL, NULL);
//    wglDeleteContext(temp_rc);
//    wglMakeCurrent(device_context, opengl_render_context);


    printf("%s\n", glGetString(GL_VERSION));

    // Triangle vertices
    float vertices[24] = {  -0.5f, -0.5f,  0.5f,
                             0.5f, -0.5f,  0.5f,
                             0.5f,  0.5f,  0.5f,
                            -0.5f,  0.5f,  0.5f,
                            // back
                            -0.5f, -0.5f, -0.5f,
                             0.5f, -0.5f, -0.5f,
                             0.5f,  0.5f, -0.5f,
                            -0.5f,  0.5f, -0.5f };

    float tex_coords[32] = { 0.0f, 0.0f,
                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f,
                             0.0f, 0.0f,
                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f,
                             0.0f, 0.0f,
                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f,
                             0.0f, 0.0f,
                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f };

    unsigned short indices[36] = { // front
                                    0, 1, 2,
                                    2, 3, 0,
                                    // right
                                    1, 5, 6,
                                    6, 2, 1,
                                    // back
                                    7, 6, 5,
                                    5, 4, 7,
                                    // left
                                    4, 0, 3,
                                    3, 7, 4,
                                    // bottom
                                    4, 5, 1,
                                    1, 0, 4,
                                    // top
                                    3, 2, 6,
                                    6, 7, 3 };

    unsigned int VBO;
    unsigned int VAO;
    unsigned int IBO;
    unsigned int TBO;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // creating and binding a vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //unsigned int VBO;
    // creating and binding a vertex buffer object(VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // specifying the attributes(details) of the vertex buffer object(VBO) we just binded (must be bounded) also enabling it
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // creating and binding a index buffer object(IBO)
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //generating texture-coordinates buffer object(TBO)
    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords), tex_coords, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, false, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    /// setting texture attributes

    // creating a texture object (texture)
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // setting texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // setting border colour
    float border_colour[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_colour);

    // setting filter options min/mag
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // loading image
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char* image = stbi_load("logo.png", &width, &height, &channels, 0);

    if(image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        printf("failed to load image requested!!");
    }

    unsigned int texture_2;
    glGenTextures(1, &texture_2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_2);

    // setting texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // setting border colour
//    float border_colour[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_colour);

    // setting filter options min/mag
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // loading image
    //stbi_set_flip_vertically_on_load(true);
//    int width, height, channels;
    image = stbi_load("bootleg.jpg", &width, &height, &channels, 0);

    if(image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        printf("failed to load image requested!!");
    }

    stbi_image_free(image);

    unsigned int shader_vertex;
    unsigned int shader_fragment;

    // retrieviing handle to the a vertex shader
    shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    // giving the actual shader source code to the handler(shader_vertex)
    glShaderSource(shader_vertex, 1, &vertex_shader, NULL);
    // compiling the shader
    glCompileShader(shader_vertex);

    int status;
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &status);
    if(!status){
        int size;
        glGetShaderiv(shader_vertex, GL_INFO_LOG_LENGTH, &size);
        char error[size];
        glGetShaderInfoLog(shader_vertex, size, &size, error);
        printf("failed to compile vertex shader: %s\n", error);
    }

    // retrieviing handle to the a fragment shader
    shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // giving the actual shader source code to the handler(shader_fragment)
    glShaderSource(shader_fragment, 1, &fragment_shader, NULL);
    // compiling the shader
    glCompileShader(shader_fragment);

    //int status;
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &status);
    if(!status){
        int size;
        glGetShaderiv(shader_fragment, GL_INFO_LOG_LENGTH, &size);
        char error[size];
        glGetShaderInfoLog(shader_fragment, size, &size, error);
        printf("failed to compile fragment shader: %s\n", error);
    }


    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, shader_vertex);
    glAttachShader(shader_program, shader_fragment);
    glLinkProgram(shader_program);

    glValidateProgram(shader_program);
    glDeleteShader(shader_vertex);
    glDeleteShader(shader_fragment);
    glUseProgram(shader_program);
    //glViewport(0, 0, 640, 480);

    glEnable(GL_DEPTH_TEST);

    glUniform1i(glGetUniformLocation(shader_program, "texel"), 0);
    glUniform1i(glGetUniformLocation(shader_program, "texel_2"), 1);

    camera cam(vector3f(0.0f, 0.0f, -1.5f));

    transformation transform;
    transform.set_camera(cam);
    transform.set_projection(70.0f, 480, 640, 0.1f, 1000.0f);
    matrix4x4 proj = transform.get_projected_transformation();
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "u_mvp"), 1, 0, &proj.m[0][0]);

    int rand_color = glGetUniformLocation(shader_program, "rand_color");


    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %d\n", err);
    }
    bool quit = false;

    glClearColor(0, 0, 0, 0);

    while(!quit){

        if(PeekMessage(&context.msg, NULL, 0, 0, PM_REMOVE)){

            if (context.msg.message == WM_QUIT){
                quit = TRUE;
            }else if (context.msg.message == WM_KEYDOWN){
                switch (context.msg.wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;

                case KEY_W:
                  transformation::Camera.move(transformation::Camera.get_forward(), 0.05f);
                  break;

                case KEY_S:
                  transformation::Camera.move(transformation::Camera.get_forward(), -0.05f);
                  break;

                case KEY_A:
                  transformation::Camera.move(transformation::Camera.get_left(), 0.05f);
                  break;

                case KEY_D:
                  transformation::Camera.move(transformation::Camera.get_right(), 0.05f);
                  break;
            }
            }else{
                TranslateMessage(&context.msg);
                DispatchMessage(&context.msg);
            }
        }

        transform.set_translation(0, 0, 0);
        matrix4x4 proj = transform.get_projected_transformation();

        glUniform4f(rand_color, (float)(rand() % 255 + 1)/255, (float)(rand() % 255 + 1)/255, (float)(rand() % 255 + 1)/255, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, 0);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "u_mvp"), 1, 0, &proj.m[0][0]);

        transform.set_translation(2, 0, 0);
        proj = transform.get_projected_transformation();

        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, 0);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "u_mvp"), 1, 0, &proj.m[0][0]);

        SwapBuffers(context.device_context);

    }

    return 0;
}
