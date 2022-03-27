#ifndef SHADER
#define SHADER

#include "glad/glad.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{
    unsigned int ID;
    std::string FolderShaderPath = "../Shaders/";
public:
    Shader(std::string vertexFile,  std::string fragmentFile);
    ~Shader();

    void use();

    void setUniform(const std::string name, int value);
    void setUniform(const std::string name, float value);
    void setUniform(const std::string name, bool value);
};

#endif