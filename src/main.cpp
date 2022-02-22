#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

int winSizeX = 640;
int winSizeY = 480;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height)
{
    winSizeX = width;
    winSizeY = height;
    glViewport(0, 0, winSizeX, winSizeY);
    std::cout << "You sus\n";
}

void glfwKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, true);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(winSizeX , winSizeY, "Hello World", NULL, NULL);
    if (!pWindow) {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        std::cout << "Glad not loaded";
        return -1;
    }
    
    std::cout << "Render: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL " << glGetString(GL_VERSION) << '\n';

    glClearColor(0, 0, 1, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}