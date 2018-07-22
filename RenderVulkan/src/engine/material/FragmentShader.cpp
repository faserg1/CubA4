#include "./FragmentShader.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

FragmentShader::FragmentShader(std::shared_ptr<Device> device, VkShaderModule shaderModule) :
	Shader(device, shaderModule)
{
	
}

FragmentShader::~FragmentShader()
{
	
}

ShaderType FragmentShader::getType() const
{
	return ShaderType::Fragment;
}