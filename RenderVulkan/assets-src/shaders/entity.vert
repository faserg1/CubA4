#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inUVW;

layout (location = 2) in mat4 entityTransformation;

layout (location = 1) out vec3 outUVW;


layout(set = 0, binding = 0) uniform Matricies
{
	ivec3 viewChunkPos;
	//layout(offset = 16, row_major) mat4 view;
	//layout(offset = 80, row_major) mat4 proj;
	layout(offset = 16) mat4 view;
	layout(offset = 80) mat4 proj;
} matricies;

/*layout(set = 1, binding = 1) uniform
{
	ivec3 chunkPos;
	layout(offset = 16) mat4 transform;
} entityInfo;*/

layout( push_constant ) uniform Constants
{
	ivec3 chunkPos;
} pushConstants;

layout (constant_id = 0) const int ChunkSize = 1;

void main()
{
	outUVW = inUVW;
	ivec3 chunkFromView = (pushConstants.chunkPos - matricies.viewChunkPos) * ChunkSize;
	vec3 transformedVertex = inPos + chunkFromView;
	vec4 sub = vec4(transformedVertex.x, transformedVertex.y, transformedVertex.z, 1.0);
	//sub.y *= -1.0;
	outUVW.y - 1;
	//gl_Position = sub * matricies.view * matricies.proj;
	gl_Position = matricies.proj * matricies.view * entityTransformation * sub;
	// gl_Position.z = (gl_Position.z + gl_Position.w) / 2;
}