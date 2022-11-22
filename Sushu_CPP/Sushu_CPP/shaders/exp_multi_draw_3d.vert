#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in uint drawid;

layout(std430, binding = 0) buffer matrices
{
    mat4 matrices_SSBO[];
};

out vec3 oColor;
flat out uint drawId;

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform float time;


void main(void) 
{
	gl_Position = projection * camera * matrices_SSBO[drawid] * vec4(position, 1.0f);
	oColor = color;
	oColor.x = sin((time * 0.001) * drawid);
	oColor.y = cos(time * 0.1);
	oColor.z = tan(time * 0.1);
	drawId = drawid;
}

