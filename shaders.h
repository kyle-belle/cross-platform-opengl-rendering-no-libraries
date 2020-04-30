#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED


static const char* vertex_shader = "#version 330\n"
                     "layout (location = 0) in vec3 vertices;\n"
                     "layout (location = 2) in vec2 tex_coords;\n"

                     "uniform mat4 u_mvp;\n"

                     "out vec2 frag_tex;\n"
                     ""
                     "  void main(){\n"
                     //"      pos_color = vec4(vertices, 1.0);\n"
                     "      frag_tex = tex_coords;\n"
                     "      gl_Position = vec4(vertices, 1.0) * u_mvp;\n"
                     "  }";

static const char* fragment_shader = "#version 330\n"
                                     "out vec4 color;\n"

                                     "uniform vec4 rand_color;\n"
                                     "uniform sampler2D texel;\n"
                                     "uniform sampler2D texel_2;\n"

                                     "in vec2 frag_tex;\n"
                                     ""
                                     "  void main(){\n"
                                     "      color = vec4(mix(/*clamp(rand_color, 0.0, 1.0) */ texture(texel, frag_tex), texture(texel_2, frag_tex), 0.3));\n"
                                     "  }";


#endif // SHADERS_H_INCLUDED
