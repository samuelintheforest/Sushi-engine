#version 450 core

out vec4 FragColor;

in vec3 oColor;
flat in uint drawId;

void main(void)
{
	FragColor = vec4(oColor.xyz, 1.0f);
}