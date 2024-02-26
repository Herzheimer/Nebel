#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

uniform mat4 mvp = mat4(1);

void main()
{
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
