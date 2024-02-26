#version 330 core
out vec4 FragColor;
in vec2 texcoords;

uniform vec4 Color = vec4(1.0);
uniform sampler2D image;
void main()
{
   FragColor = texture(image, texcoords) * Color;
}