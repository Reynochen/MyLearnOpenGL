#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"
#include "stb_image.h"
#include <math.h>
//GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void camera_pin();

float scale = 1;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool forward, backward, left, right;

//Screen
int winWidth = 1920, winHeight = 1080;

//Player
glm::vec3 playerPos = glm::vec3(0.0f, 0.0f, 3.0f);

//Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 direction;

float distanceFromPlayer = 3;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = winWidth / 2, lastY = winHeight / 2;
const float sensivity = 10.0f;

bool firstMouse = true;

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "Create by Reynochen", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //Make the window's context current */
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
    /*float vertices[] {
        //Coords triangle       //Colors    //Texture coords
        //x     y     z         r  g  b     s     t
        -0.5f, -0.5f, 0.0f,     1, 1, 0,    0.0f, 0.0f, //низ лево
        -0.5f, 0.5f, 0.0f,      0, 0, 1,    0.0f, 1.0f, //вверх лево
        0.5f, 0.5f, 0.0f,       0, 0, 1,    1.0f, 1.0f, //вверх право
        0.5f, -0.5f, 0.0f,      1, 1, 0,    1.0f, 0.0f, //низ право
    };*/

    unsigned int index[] {
        2, 0, 1,
        0, 3, 2,       
    };

    float vertices[] {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    //Cube position
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 0.0f,  1.0f,  0.0f), 
        glm::vec3( 0.0f,  2.0f,  0.0f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    //Create texture
    unsigned int texture[2];
    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //Texture1 options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    //Load wall texture
    int width, height, nrChannels;
    unsigned char *data;
    
    data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    Shader shader("Red.vs", "Red.fs");

    shader.use();
    shader.setUniform("texture1", 0);
    shader.setUniform("texture2", 1);

    unsigned int modelLoc = glGetUniformLocation(shader.getID(), "model");
    unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
    unsigned int projectionLoc = glGetUniformLocation(shader.getID(), "projection");
    
    //Матрицы для пространства
    glm::mat4 model = glm::mat4(1.0f);    

    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(100.0f), (float)(winWidth) / (float)(winHeight), 0.1f, 100.0f);

    //Enable z-buffer
    glEnable(GL_DEPTH_TEST);
    
    
    //Cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        shader.use();
        shader.setUniform("scale", scale);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glBindVertexArray(vao);
        for (int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if(i % 3 == 0)
                model = glm::rotate(model, glm::radians((float)(glfwGetTime() * (i + 1) * 30)), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        //Player draw;
        model = glm::mat4(1.0f);
        model = glm::translate(model, playerPos);
        shader.setUniformColor("globColor", 0.1f, 0.8f, 0.2f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        shader.setUniformColor("globColor", 1, 1, 1);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        processInput(window);
        //Camera
        camera_pin();
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

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

void camera_pin()
{
    float horizDistance = distanceFromPlayer * cos(glm::radians(pitch));
    float vertDistance = distanceFromPlayer * sin(glm::radians(pitch));
    
    float offsetX = (float)(horizDistance * sin(glm::radians(yaw)));
    float offsetZ = (float)(horizDistance * cos(glm::radians(yaw)));

    cameraPos.x = playerPos.x - offsetZ;
    cameraPos.z = playerPos.z - offsetX;
    cameraPos.y = playerPos.y - vertDistance;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    yaw += xoffset * sensivity * deltaTime;
    pitch += yoffset * sensivity * deltaTime;
    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
       pitch = -89.0f;
    
    
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraFront = glm::normalize(dir);
}

void processInput(GLFWwindow* window)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraSpeed = 5.5f * deltaTime;
    else
        cameraSpeed = 2.5f * deltaTime;

    direction.x = cos(glm::radians(yaw));
    direction.z = sin(glm::radians(yaw));
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        playerPos += cameraSpeed * direction;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        playerPos -= cameraSpeed * direction;    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        playerPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        playerPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        playerPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        playerPos -= cameraUp * cameraSpeed;
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
    case GLFW_KEY_E:
        if(action == GLFW_PRESS)
            glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        else if(action == GLFW_RELEASE)
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        break;
    case GLFW_KEY_UP:
        if(action != GLFW_RELEASE)
            scale -= 1;
        break;
    case GLFW_KEY_DOWN:
        if(action != GLFW_RELEASE)
            scale += 1;
        break;
    }
}