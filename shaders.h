#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED

//#define OBJECT_VERTEX_BUFFER 0
//#define OBJECT_NORMAL_BUFFER 1
//#define OBJECT_TEX_COORD_BUFFER 2
//#define OBJECT_INDEX_BUFFER 3


static const char* vertex_shader = "#version 330\n"
                     "layout (location = 0) in vec3 vertices;\n"
                     "layout (location = 1) in vec3 normals;\n"
                     "layout (location = 2) in vec2 tex_coords;\n"

                     "uniform mat4 u_mvp;\n"
                     "uniform mat4 model;\n"

                     "out vec2 frag_tex;\n"
                     "out vec3 vertex_normal;\n"
                     "out vec3 frag_pos;\n"

                     "  void main(){\n"
                     //"      pos_color = vec4(vertices, 1.0);\n"
                     "      gl_Position = vec4(vertices, 1.0) * u_mvp;\n"
                     "      vertex_normal = normals;\n"
                     "      frag_tex = tex_coords;\n"
                     "      frag_pos = vec3(model * vec4(vertices, 1.0));\n"
                     "  }";


static const char* fragment_shader = "#version 330\n"
                                     "out vec4 color;\n"

                                     "uniform vec4 rand_color;\n"
                                     "uniform sampler2D texel;\n"
                                     "uniform sampler2D texel_2;\n"
                                     "uniform vec4 object_color;\n"
                                     "uniform vec4 light_color;\n"
                                     "uniform vec3 light_pos;\n"

                                     "in vec2 frag_tex;\n"
                                     "in vec3 frag_pos;\n"
                                     "in vec3 vertex_normal;\n"
                                     ""
                                     "  void main(){\n"
                                     "      float ambient_strength = 0.3;\n"
                                     "      vec3 normal = normalize(vertex_normal);\n"
                                     "      vec3 light_direction = normalize(light_pos - frag_pos);\n"
                                     "      float diffuse_factor = max(dot(normal, light_direction), 0.0);\n"
                                     "      vec3 diffuse_color = diffuse_factor * light_color.xyz;\n"
                                     "      vec3 ambient = ambient_strength * light_color.xyz;\n"
                                     "      vec3 result = (ambient + diffuse_color) * object_color.xyz;\n"
                                     "      color = vec4(result, 1.0);\n"
                                     "  }";

static const char* light_fragment_shader = "#version 330\n"
                                     "out vec4 color;\n"

                                     "uniform vec4 light_color;\n"

                                     "in vec2 frag_tex;\n"
                                     ""
                                     "  void main(){\n"
                                     "      color = vec4(light_color.xyz, 1.0);\n"
                                     "  }";


#endif // SHADERS_H_INCLUDED
