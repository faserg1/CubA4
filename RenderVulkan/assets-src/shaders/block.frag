#version 450

layout (location = 1) in vec3 inUVW;
layout (location = 0) out vec4 outColor;
layout (set = 1, binding = 2) uniform sampler2D inTexture;

void main()
{
	outColor = texture(inTexture, vec2(inUVW.st));
}