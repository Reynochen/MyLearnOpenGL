#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Create by Reynochen", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Glad not loaded";
        return -1;
    }    
    //Callback window resize and callback key
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallBack);
    glfwSetKeyCallback(window, glfwKeyCallBack);

    std::cout << "Render: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL " << glGetString(GL_VERSION) << '\n';


    float vertices[] {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f, 0.5f, 0.0f
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    Shader shader("Red.vs","Red.fs");

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if(action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        break;
    }
}