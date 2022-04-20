#version 330 core

in vec3 pos;
in vec3 aNormal;

out vec3 normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1);
    FragPos = vec3(model * vec4(pos, 1.0));
    normal = mat3(transpose(inverse(model))) * aNormal;
}