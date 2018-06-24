#include "./InstanceBuilder.hpp"
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
#include <stdexcept>
#include <algorithm>
#include <info/IApplicationInfo.hpp>
#include <info/IVersion.hpp>
#include "addon/InstanceExtension.hpp"
#include "addon/InstanceLayer.hpp"
#include "Instance.hpp"
using namespace CubA4::render::vulkan;
using namespace CubA4::core::info;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			struct InstanceBuilderData
			{
				VkApplicationInfo appInfo;
				VkInstanceCreateInfo instanceInfo;
			};
		}
	}
}

InstanceBuilder::InstanceBuilder(std::shared_ptr<const IApplicationInfo> info) :
	data_(std::make_shared<InstanceBuilderData>()), info_(info)
{
	memset(&(*data_), 0, sizeof(InstanceBuilderData));
	data_->instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	data_->instanceInfo.pApplicationInfo = &data_->appInfo;
	data_->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	fillAppInfo();
}

InstanceBuilder::~InstanceBuilder()
{
	
}

void InstanceBuilder::addLayer(addon::InstanceLayer &layer)
{
	if (!layer.available())
		throw std::runtime_error("Extension is not available");
	auto names = layer.names();
	layers_.insert(layers_.end(), names.begin(), names.end());
	layer.added(*this);
}

void InstanceBuilder::addExtension(addon::InstanceExtension &extension)
{
	if (!extension.available())
		throw std::runtime_error("Extension is not available");
	auto names = extension.names();
	extensions_.insert(extensions_.end(), names.begin(), names.end());
	extension.added(*this);
}

std::shared_ptr<const Instance> InstanceBuilder::build()
{
	std::vector<const char *> cStrExtensions(extensions_.size());
	std::vector<const char *> cStrLayers(layers_.size());
	std::transform(extensions_.begin(), extensions_.end(), cStrExtensions.begin(), [](std::string &str) {return str.c_str(); });
	std::transform(layers_.begin(), layers_.end(), cStrLayers.begin(), [](std::string &str) {return str.c_str(); });
	data_->instanceInfo.enabledExtensionCount = cStrExtensions.size();
	data_->instanceInfo.ppEnabledExtensionNames = cStrExtensions.data();
	data_->instanceInfo.enabledLayerCount = cStrLayers.size();
	data_->instanceInfo.ppEnabledLayerNames = cStrLayers.data();

	VkInstance instance;
	if (vkCreateInstance(&data_->instanceInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("Unable to create Vulkan Instance");

	return std::make_shared<Instance>(instance);
}

void InstanceBuilder::destroy(std::shared_ptr<const Instance> instance)
{
	auto vkInst = instance->getInstance();
	vkDestroyInstance(vkInst, nullptr);
}

void InstanceBuilder::fillAppInfo()
{
	data_->appInfo.pApplicationName = info_->name().c_str();
	auto &appVer = info_->version();
	data_->appInfo.applicationVersion = VK_MAKE_VERSION(appVer.major(), appVer.minor(), appVer.patch());
	data_->appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 0);
}
