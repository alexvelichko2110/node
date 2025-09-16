#version 330 core

in vec2 TexCoord;

out vec4 color;


uniform sampler2D ourTexture;
uniform vec4 ourColor;


void main()
{
    color = vec4(1, 1, 1, texture(ourTexture, TexCoord).a) * ourColor;
}
