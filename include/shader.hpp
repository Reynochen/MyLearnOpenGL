#ifndef SHADER
#define SHADER

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <iostream>

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
};

#endif