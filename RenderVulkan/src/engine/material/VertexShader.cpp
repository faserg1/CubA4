#include "./VertexShader.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

VertexShader::VertexShader(std::shared_ptr<Device> device, VkShaderModule shaderModule) :
	Shader(device, shaderModule)
{
	
}

VertexShader::~VertexShader()
{
	
}

ShaderType VertexShader::getType() const
{
	return ShaderType::Vertex;
}