#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

out vec4 vColor;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

void main()
{
  vColor = aCol;
  gl_Position = projection * camera * model * vec4(aPos, 1.0);
}


