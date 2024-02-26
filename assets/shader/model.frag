#version 330 core
out vec4 FragColor;
uniform vec4 Color = vec4(1.0);
void main()
{
   FragColor = Color;
}