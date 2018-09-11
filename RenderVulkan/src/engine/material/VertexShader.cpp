#include "./VertexShader.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

VertexShader::VertexShader(std::shared_ptr<const Device> device, VkShaderModule shaderModule, std::string entryPoint) :
	Shader(device, shaderModule, entryPoint)
{
	
}

VertexShader::~VertexShader()
{
	
}

ShaderType VertexShader::getType() const
{
	return ShaderType::Vertex;
}