#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

//Default options
float YAW = -90.0f;
float PITCH = 0.0f;
float SENSIVITY = 0.1f;
float SPEED = 3.5f;
float FOV = 80.0f;

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
glm::vec3 Position;
glm::vec3 Front;
glm::vec3 Up;
glm::vec3 Right;
glm::vec3 WorldUp;

float yaw;
float pitch;

float speed;
float sensivity;
float fov;

public:
    Camera(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), 
    float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensivity(SENSIVITY), fov(FOV) 
    {
        this->yaw = yaw;
        this->pitch = pitch;

        Position = cameraPos;
        WorldUp = Up;

        UpdateVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Front + Position, Up);
    }

    void MouseMove(float xoffset, float yoffset)
    {
        yaw += xoffset * sensivity;
        pitch += yoffset * sensivity;
    
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        UpdateVectors();
    }

    float getFov()
    {
        return fov;
    }

    void CameraMove(Direction dir, float deltaTime)
    {
        if(dir == FORWARD)
            Position += Front* speed * deltaTime;
        if(dir == BACKWARD)
            Position -= Front * speed * deltaTime;
        if(dir == RIGHT)
            Position += Right * speed * deltaTime;
        if(dir == LEFT)
            Position -= Right * speed * deltaTime;  
    }

    glm::vec3 getPos()
    {
        return Position;
    }
private:
    void UpdateVectors()
    {    
        glm::vec3 dir;
        dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        dir.y = sin(glm::radians(pitch));
        dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        Front = glm::normalize(dir);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};



#endif