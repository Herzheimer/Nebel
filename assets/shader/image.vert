#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 mvp = mat4(1);

out vec2 texcoords;
void main()
{
   texcoords = aTexCoords;
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
