#include "./MaterialFactory.hpp"
#include "./MaterialBuilder.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialFactory::MaterialFactory(std::shared_ptr<const Device> device, std::shared_ptr<const DescriptorPool> pool) :
	device_(device), pool_(pool)
{
	createSampler();
}

MaterialFactory::~MaterialFactory()
{
	vkDestroySampler(device_->getDevice(), sampler_, nullptr);
}

std::shared_ptr<IMaterialBuilder> MaterialFactory::createMaterial(std::shared_ptr<const IMaterialLayout> layout)
{
	return std::make_shared<MaterialBuilder>(device_, pool_, layout, sampler_);
}

void MaterialFactory::createSampler()
{
	VkSamplerCreateInfo info {
		.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.magFilter = VK_FILTER_NEAREST,
		.minFilter = VK_FILTER_NEAREST,
		.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
		.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
	};
	vkCreateSampler(device_->getDevice(), &info, nullptr, &sampler_);
}