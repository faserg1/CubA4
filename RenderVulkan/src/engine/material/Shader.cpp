#include "./Shader.hpp"
#include "../../vulkan/Device.hpp"
#include <vulkan/vulkan.h>
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

Shader::Shader(std::shared_ptr<Device> device, VkShaderModule shaderModule) :
	device_(device), shaderModule_(shaderModule)
{
	
}

Shader::~Shader()
{
	vkDestroyShaderModule(device_->getDevice(), shaderModule_, nullptr);
}

