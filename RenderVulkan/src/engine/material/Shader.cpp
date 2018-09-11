#include "./Shader.hpp"
#include "../../vulkan/Device.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

Shader::Shader(std::shared_ptr<const Device> device, VkShaderModule shaderModule, std::string entryPoint) :
	device_(device), shaderModule_(shaderModule), entryPoint_(entryPoint)
{
	
}

Shader::~Shader()
{
	vkDestroyShaderModule(device_->getDevice(), shaderModule_, nullptr);
}

VkShaderModule Shader::getShaderModule() const
{
	return shaderModule_;
}

const std::string &Shader::getEntryPoint() const
{
	return entryPoint_;
}