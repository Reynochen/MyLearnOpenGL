#include "shader.hpp"

Shader::Shader(std::string vertexFile,  std::string fragmentFile)
{
    std::string vertexBuffer;
    std::string fragmentBuffer;

    std::ifstream openFile;

    openFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    try
    {
        std::stringstream streamCode;
        std::stringstream streamCode2;

        openFile.open(this->FolderShaderPath + vertexFile);
        streamCode << openFile.rdbuf();
        openFile.close();

        vertexBuffer = streamCode.str();

        openFile.open(this->FolderShaderPath + fragmentFile);
        streamCode2 << openFile.rdbuf();
        openFile.close();

        fragmentBuffer = streamCode2.str();
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR SHADER Cant load shader file" << '\n';
    }
    
    const char* vertexCode = vertexBuffer.c_str();
    const char* fragmentCode = fragmentBuffer.c_str();

    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    //Create Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX compilation failed\n" << infoLog << '\n';
    }

    //Create Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "SHADER::FRAGMENT compilation failed\n" << infoLog << '\n';
    }

    //Create program shader
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "SHADER::PROGRAM link failed\n" << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::setUniform(const std::string name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniform(const std::string name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setUniform(const std::string name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}