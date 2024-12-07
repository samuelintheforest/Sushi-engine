#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aPxVal;
layout (location = 2) in float aIsTx;

out vec4 vPxVal;
out float vIsTx;

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

void main()
{
  vPxVal = aPxVal;
  vIsTx = aIsTx;
  gl_Position = projection * camera * model * vec4(aPos, 1.0);
}


