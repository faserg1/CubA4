#version 450

layout (location = 0) out vec4 outColor;
layout (location = 1) in vec3 inColor;

void main()
{
	outColor = vec4(inColor, 1);
}