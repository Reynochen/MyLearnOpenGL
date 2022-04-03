#version 330 core

out vec4 FragColor;

in vec3 out_color;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord) * vec4(out_color, 1.0f);
}