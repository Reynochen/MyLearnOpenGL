#version 330 core

in vec3 pos;
in vec2 aTexCoord;
in vec3 color;

out vec3 out_color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
    out_color = color;
    TexCoord = aTexCoord;
}