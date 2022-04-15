#version 330 core

in vec3 pos;
in vec3 color;
in vec2 aTexCoord;

out vec3 out_color;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(pos.x, pos.y, pos.z, 1.0);
    out_color = color;
    TexCoord = aTexCoord;
}