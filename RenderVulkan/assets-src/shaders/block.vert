#version 450

layout (location = 0) in vec3 inPos;
layout (location = 0) out vec4 outPos;

layout (location = 1) in vec3 inUVW;
layout (location = 1) out vec3 outUVW;


layout(binding = 0, row_major) uniform Matricies
{
	ivec3 viewChunkPos;
	mat4 view;
	mat4 proj;
} matricies;

layout( push_constant ) uniform Constants
{
	ivec3 chunkPos;
} pushConstants;

layout (constant_id = 0) const int ChunkSize = 1;

void main()
{
	outUVW = inUVW;
	vec3 chunkFromView = (pushConstants.chunkPos - matricies.viewChunkPos) * ChunkSize;
	vec3 transformedVertex = inPos + chunkFromView;
	vec4 sub = vec4(transformedVertex.x, transformedVertex.y, transformedVertex.z, 1.0);
	sub.y *= -1.0;
	outUVW.y - 1;
	outPos = sub * matricies.view * matricies.proj;
	outPos.z = (outPos.z + outPos.w) / 2;
}