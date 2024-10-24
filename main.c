#include <stdio.h>
#include <cglm/call/vec2.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/core.h"
#include "graphics/buffer.h"
#include "graphics/shader.h"
#include "graphics/utils.h"

int main(void)
{
    kck_graphics_context context = kck_initialize_context();

    float vertices[] = {
        1.0f,  1.0f, 0.0f,  // top right
        1.0f, -1.0f, 0.0f,  // bottom right
       -1.0f, -1.0f, 0.0f,  // bottom left
       -1.0f,  1.0f, 0.0f   // top left
   };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    float uv[] =
        {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
        };

    kck_shader vertex_shader = kck_create_shader(KCK_VERTEX_SHADER);
    kck_load_shader(&vertex_shader, "local/shaders/default_vertex.glsl");

    kck_shader fragment_shader = kck_create_shader(KCK_FRAGMENT_SHADER);
    kck_load_shader(&fragment_shader, "local/shaders/default_frag.glsl");

    kck_shader_program program = kck_create_shader_program();
    kck_load_shader_program(&program, &vertex_shader, &fragment_shader);

    kck_vao vao = kck_create_vao();

    kck_vertex_buffer buffer = kck_create_vertex_buffer(12);
    kck_put_vertex_buffer(&buffer, vertices, 12);
    kck_create_vertex_attrib_pointer(0, 3, GL_FLOAT);

    kck_vertex_buffer uv_buffer = kck_create_vertex_buffer(8);
    kck_put_vertex_buffer(&uv_buffer, uv, 8);
    kck_create_vertex_attrib_pointer(1, 2, GL_FLOAT);


    kck_index_buffer i_buffer = kck_create_index_buffer(6);
    kck_put_index_buffer(&i_buffer, indices, 6);

    kck_store_buffer_in_vao(&vao, &buffer.buffer, KCK_VERTEX_BUFFER);
    kck_store_buffer_in_vao(&vao, &i_buffer.buffer, KCK_INDEX_BUFFER);

    float i = 0;

    vec2 resolution;

    resolution[0] = context.window.width;
    resolution[1] = context.window.height;

    while (!glfwWindowShouldClose(context.window.glfwWindow)) {
        kck_begin_loop(&context);

        i += 0.01f;

        glUseProgram(program.id);


        kck_upload_shader_uniform_vec2(&program, "resolution", &resolution);
        kck_upload_shader_uniform_float(&program, "delta", i);

        kck_draw_indexed(&vao, &program);

        kck_end_loop(&context);
    }
    kck_destroy(&context);
}
