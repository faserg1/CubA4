#include "./ShaderFactory.hpp"
#include <vulkan/vulkan.h>
#include "../../vulkan/Device.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

ShaderFactory::ShaderFactory(std::shared_ptr<const Device> device) :
	device_(device)
{
	
}

ShaderFactory::~ShaderFactory()
{
	
}

std::shared_ptr<IShader> ShaderFactory::createFromBinary(const void *data, size_t size, ShaderType type) const
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pCode = reinterpret_cast<const uint32_t*>(data);
	createInfo.codeSize = size;
	VkShaderModule shaderModule;
	auto result = vkCreateShaderModule(device_->getDevice(), &createInfo, nullptr, &shaderModule);
	if (result != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception
		return {};
	}
	switch (type)
	{
	case ShaderType::Fragment:
		return std::make_shared<FragmentShader>(device_, shaderModule);
	case ShaderType::Vertex:
		return std::make_shared<VertexShader>(device_, shaderModule);
	default:
		//TODO: [OOKAMI] Exception
		return {};
	}
}