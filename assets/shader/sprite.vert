#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 mvp = mat4(1);
uniform vec2 row_column_indices = vec2(0);
uniform vec2 row_column_count = vec2(1);

out vec2 texcoords;
void main()
{
   texcoords = (aTexCoords/row_column_count)+(row_column_indices/row_column_count);
   gl_Position = mvp * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
