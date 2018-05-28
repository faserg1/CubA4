#include "./VulkanInstanceLayer.hpp"
#include <vulkan/vulkan.h>
#include <stdexcept>
using namespace CubA4::render::vulkan::addon;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanLayerPrivate
				{
					std::vector<VkLayerProperties> layers;
				};
			}
		}
	}
}

VulkanInstanceLayer::VulkanInstanceLayer() :
	data_(std::make_shared<VulkanLayerPrivate>())
{
	uint32_t layersCount = 0;
	if (vkEnumerateInstanceLayerProperties(&layersCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance layers.");
	data_->layers.resize(layersCount);
	if (vkEnumerateInstanceLayerProperties(&layersCount, data_->layers.data()) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance layers.");
}

VulkanInstanceLayer::~VulkanInstanceLayer()
{
	
}

std::vector<std::string> CubA4::render::vulkan::addon::VulkanInstanceLayer::allNames() const
{
	std::vector<std::string> all;
	all.reserve(data_->layers.size());
	for (VkLayerProperties &layerProp : data_->layers)
		all.push_back(layerProp.layerName);
	return all;
}

