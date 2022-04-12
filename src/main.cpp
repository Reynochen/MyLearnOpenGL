#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"
#include "stb_image.h"

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

    //Coords triangle
    float vertices[] {
        //Coords triangle       //Colors    //Texture coords
        //x     y     z
        -0.5f, -0.5f, 0.0f,     1, 1, 0,    0.0f, 0.0f, //низ лево
        -0.5f, 0.5f, 0.0f,      0, 0, 1,    0.0f, 1.0f, //вверх лево
        0.5f, 0.5f, 0.0f,       0, 0, 1,    1.0f, 1.0f, //вверх право
        0.5f, -0.5f, 0.0f,      1, 1, 0,    1.0f, 0.0f, //низ право
    };

    unsigned int index[] {
        2, 0, 1,
        0, 3, 2,       
    };

    //Create texture
    unsigned int texture[2];
    glGenTextures(2, texture);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //Texture1 options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    //Load wall texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load wall texture." << '\n';
    }
    stbi_image_free(data);
    
    //Load que pro texture
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    data = stbi_load("que pro.png", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load que pro texture." << '\n';
    }
    stbi_image_free(data);

    //Create vao & vbo & ebo
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    Shader shader("Red.vs","Red.fs");
    
    shader.use();
    shader.setUniform("texture1", 0);
    shader.setUniform("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

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
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        else if(action == GLFW_RELEASE)
            glfwSetWindowShouldClose(window, true);
        break;
    case GLFW_KEY_W:
        if(action == GLFW_PRESS)
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        else if(action == GLFW_RELEASE)
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        break;
    }
}