#include "./Shader.hpp" 
#include "./Device.hpp"
#include "../../gen/irs.hpp"
#include <stdexcept>
using namespace CubA4::render::vulkan;

Shader::Shader(std::shared_ptr<Device> device, const void *data, size_t size) :
	device_(device)
{
	VkShaderModuleCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	info.pCode = reinterpret_cast<const uint32_t *>(data);
	info.codeSize = size;
	if (vkCreateShaderModule(device_->getDevice(), &info, nullptr, &module_) != VK_SUCCESS)
		throw std::runtime_error("Fail to create shader module!");
}

Shader::~Shader()
{
	vkDestroyShaderModule(device_->getDevice(), module_, nullptr);
}

VkShaderModule Shader::getModule() const
{
	return module_;
}

std::shared_ptr<Shader> Shader::fromIrs(std::shared_ptr<Device> device, const char *name)
{
	size_t size;
	const void *data = CubA4::irs::findFile(name, size);
	if (!data)
		return std::shared_ptr<Shader>();
	return std::shared_ptr<Shader>(new Shader(device, data, size), [](Shader *ptr) {delete ptr;});
}