#include "shader.hpp"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexBuffer;
    std::string fragmentBuffer;

    std::ifstream openFile;
    char buffer;

    ////////////////Open file
    //Open Vertex Shader File
    openFile.open(this->FolderShaderPath + vertexFile);
    if(!openFile.is_open()) {
        std::cerr << "SHADER::ERROR cannot open file.\n"; 
        return;
    }
    while(openFile.get(buffer)) 
        vertexBuffer += buffer;
    openFile.close();

    //Open Fragment Shader File
    openFile.open(this->FolderShaderPath + fragmentFile);
    if(!openFile.is_open()) {
        std::cerr << "SHADER::ERROR cannot open file.\n"; 
        return;
    }
    while(openFile.get(buffer)) 
        fragmentBuffer += buffer;
    openFile.close();
        
    
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

unsigned int Shader::getID()
{
    return ID;
}