#include <stdio.h>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "cell.hpp"
#include "scene.hpp"
#include "shaders.hpp"
#include "texture.hpp"

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    int width = 800;
    int height = 600;
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "Element", NULL, NULL);
    if(window == NULL) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    float vertices[] = {
        // Vertices // Texcoord
        -1.0, -1.0, 0.0, 0.0,
        1.0, -1.0,  1.0, 0.0,
        -1.0, 1.0,  0.0, 1.0,
        1.0, 1.0,   1.0, 1.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    // Vertices
    unsigned int vao, v_buffer, ebo;
    glGenBuffers(1, &v_buffer);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );

    // Texture
    int tex_w = 400;
    int tex_h = 300;
    Texture texture { tex_w, tex_h };
    Scene scene { tex_w, tex_h };
    float data[tex_w * tex_h * 3];

    // Shader
    Shader shader("../shaders/shader.vert", "../shaders/shader.frag");
    shader.use();
    shader.setInt("tex", 0);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(BG_COLOR.x, BG_COLOR.y, BG_COLOR.z, 1.0f);

    float dt = 0.0f;
    float last_time = glfwGetTime();
    scene.add_cell(STEEL, 200, 100);
    scene.add_cell(STEEL, 201, 100);
    scene.add_cell(STEEL, 202, 100);
    scene.add_cell(STEEL, 200, 101);
    scene.add_cell(STEEL, 202, 101);
    scene.add_cell(WATER, 201, 150);
    scene.add_cell(WATER, 201, 200);
    scene.add_cell(WATER, 201, 203);
    scene.add_cell(WATER, 201, 204);
    scene.add_cell(WATER, 201, 208);
    while(glfwWindowShouldClose(window) == 0) {
        float current_time = glfwGetTime();
        dt = current_time - last_time;

        // Process input and update
        process_input(window);
        scene.add_cell(SAND, 100, 150);
        scene.update();

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.gen_texture(data);
        texture.render(data);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &v_buffer);
    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}