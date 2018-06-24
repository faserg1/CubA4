#include "./VulkanShader.hpp"
#include "./VulkanDevice.hpp"
#include "../../gen/irs.hpp"
#include <stdexcept>
using namespace CubA4::render::vulkan;

VulkanShader::VulkanShader(std::shared_ptr<VulkanDevice> device, const void *data, size_t size) :
	device_(device)
{
	VkShaderModuleCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	info.pCode = reinterpret_cast<const uint32_t *>(data);
	info.codeSize = size;
	if (vkCreateShaderModule(device_->getDevice(), &info, nullptr, &module_) != VK_SUCCESS)
		throw std::runtime_error("Fail to create shader module!");
}

VulkanShader::~VulkanShader()
{
	vkDestroyShaderModule(device_->getDevice(), module_, nullptr);
}

VkShaderModule VulkanShader::getModule() const
{
	return module_;
}

std::shared_ptr<VulkanShader> VulkanShader::fromIrs(std::shared_ptr<VulkanDevice> device, const char *name)
{
	size_t size;
	const void *data = CubA4::irs::findFile(name, size);
	if (!data)
		return std::shared_ptr<VulkanShader>();
	return std::shared_ptr<VulkanShader>(new VulkanShader(device, data, size), [](VulkanShader *ptr) {delete ptr;});
}