#include "./InstanceLayer.hpp" 
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
				struct InstanceLayerData 
				{
					std::vector<VkLayerProperties> layers;
				};
			}
		}
	}
}

InstanceLayer::InstanceLayer() :
	data_(std::make_shared<InstanceLayerData>())
{
	uint32_t layersCount = 0;
	if (vkEnumerateInstanceLayerProperties(&layersCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance layers.");
	data_->layers.resize(layersCount);
	if (vkEnumerateInstanceLayerProperties(&layersCount, data_->layers.data()) != VK_SUCCESS)
		throw std::runtime_error("Unable to enumerate instance layers.");
}

InstanceLayer::~InstanceLayer()
{
	
}

std::vector<std::string> CubA4::render::vulkan::addon::InstanceLayer::allNames() const
{
	std::vector<std::string> all;
	all.reserve(data_->layers.size());
	for (VkLayerProperties &layerProp : data_->layers)
		all.push_back(layerProp.layerName);
	return all;
}

