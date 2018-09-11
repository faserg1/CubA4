#include "./FragmentShader.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

FragmentShader::FragmentShader(std::shared_ptr<const Device> device, VkShaderModule shaderModule, std::string entryPoint) :
	Shader(device, shaderModule, entryPoint)
{
	
}

FragmentShader::~FragmentShader()
{
	
}

ShaderType FragmentShader::getType() const
{
	return ShaderType::Fragment;
}