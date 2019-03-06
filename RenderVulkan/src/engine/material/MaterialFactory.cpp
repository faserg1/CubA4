#include "./MaterialFactory.hpp"
#include "./MaterialBuilder.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialFactory::MaterialFactory(std::shared_ptr<const Device> device) :
	device_(device)
{
	createDescriptorPool();
}

MaterialFactory::~MaterialFactory()
{
	
}

std::shared_ptr<IMaterialBuilder> MaterialFactory::createMaterial(std::shared_ptr<const IMaterialLayout> layout)
{
	return std::make_shared<MaterialBuilder>(device_, layout, pool_);
}

void MaterialFactory::createDescriptorPool()
{
	std::vector<VkDescriptorPoolSize> sizes;

	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.maxSets = 1;

	VkDescriptorPoolSize uniforms;
	uniforms.descriptorCount = 10;
	uniforms.type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;

	sizes.push_back(uniforms);

	poolCreateInfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
	poolCreateInfo.pPoolSizes = sizes.data();

	VkDescriptorPool pool = {};

	if (vkCreateDescriptorPool(device_->getDevice(), &poolCreateInfo, nullptr, &pool) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}

	device_->getMarker().setName(pool, "Textures pool");

	std::function<void(VkDescriptorPool pool)> deleter = [dev = device_](VkDescriptorPool pool)
	{
		vkDestroyDescriptorPool(dev->getDevice(), pool, nullptr);
	};

	pool_ = util::createSharedVulkanObject(pool, deleter);
}