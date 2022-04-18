#version 330 core

out vec4 FragColor;

in vec3 out_color;
in vec2 TexCoord;

uniform vec3 globColor = vec3(1.0f, 1.0f, 1.0f);
uniform float scale;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1, TexCoord); //* vec4(out_color, 1.0f);
    FragColor = texture(texture2, TexCoord * scale) * texture(texture1, TexCoord * scale) * vec4(globColor, 1.0f);
}