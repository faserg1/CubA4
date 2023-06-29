#version 450

layout (location = 0) in vec3 inPos;
//layout (binding = 1, location = 1) in vec3 inColor;

layout(binding = 0/*, row_major*/) uniform Matricies
{
	ivec3 viewChunkPos;
	layout(offset = 16, row_major) mat4 view;
	layout(offset = 80, row_major) mat4 proj;
} matricies;

layout( push_constant ) uniform Constants
{
	ivec3 chunkPos;
} pushConstants;

layout (constant_id = 0) const int ChunkSize = 1;

void main()
{
	ivec3 chunkFromView = (pushConstants.chunkPos - matricies.viewChunkPos) * ChunkSize;
	vec3 transformedVertex = inPos + chunkFromView;
	vec4 sub = vec4(transformedVertex.x, transformedVertex.y, transformedVertex.z, 1.0);
	sub.y *= -1.0;
	gl_Position = sub * matricies.view * matricies.proj;
}