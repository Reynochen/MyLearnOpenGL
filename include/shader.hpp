#ifndef SHADER
#define SHADER

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    unsigned int ID;
    std::string FolderShaderPath = "../Shaders/";
public:
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    void use();

    unsigned int getID();
    void setUniform(const std::string name, int value);
    void setUniform(const std::string name, float value);
    void setUniform(const std::string name, bool value);
    void setMat4(const std::string name, glm::mat4 matrix);
    void setVec3(const std::string name, float x, float y, float z);
    void setVec3(const std::string name, glm::vec3 vector);
};

#endif