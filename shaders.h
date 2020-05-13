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

                                     "struct Material{\n"
                                     "  vec4 color;\n"
                                     "  float specular;\n"
                                     "  float shininess;\n"
                                     "};\n"

                                     "uniform vec4 rand_color;\n"
                                     "uniform sampler2D texel;\n"
                                     "uniform sampler2D texel_2;\n"
                                     "uniform vec3 eye_pos;\n"
                                     "uniform vec4 object_color;\n"

                                     "uniform vec4 light_color;\n"
                                     "uniform vec3 light_pos;\n"

                                     "uniform Material material;\n"
                                     "uniform float ambient_light;\n"

                                     "in vec2 frag_tex;\n"
                                     "in vec3 frag_pos;\n"
                                     "in vec3 vertex_normal;\n"

                                     "  void main(){\n"
                                     "      vec3 view_direction = normalize(eye_pos - frag_pos);\n"
                                     "      vec3 normal = normalize(vertex_normal);\n"
                                     "      vec4 texture_color = texture(texel, frag_tex);\n"
                                     "      vec3 light_direction = normalize(light_pos - frag_pos);\n"
                                     "      vec3 reflect_direction = reflect(-light_direction, normal);\n"
                                     "      float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);\n"
                                     "      vec3 specular_component = material.specular * spec * light_color.xyz;\n"
                                     "      float diffuse_factor = max(dot(normal, light_direction), 0.0);\n"
                                     "      vec3 diffuse_color = diffuse_factor * light_color.xyz;\n"
                                     "      vec3 ambient_component = ambient_light * light_color.xyz;\n"
                                     "      vec3 result = (ambient_component + diffuse_color + specular_component) * texture_color.xyz * material.color.xyz;\n"
                                     "      color = vec4(result, texture_color.w * material.color.w);\n"
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
