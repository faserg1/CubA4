#pragma once

#include <memory>
#include <functional>
#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan::util
{
	template <class TVulkanObject>
	class VulkanHandlerContainer final
	{
	public:
		explicit VulkanHandlerContainer(TVulkanObject object, std::function<void(TVulkanObject)> deleter) :
			vulkanObject_(object), deleter_(deleter)
		{
		}
		~VulkanHandlerContainer()
		{
			deleter_(vulkanObject_);
		}
		TVulkanObject get() const
		{
			return vulkanObject_;
		}
	private:
		const TVulkanObject vulkanObject_;
		const std::function<void(TVulkanObject)> deleter_;
	};

	template <class TVulkanObject>
	std::shared_ptr<VulkanHandlerContainer<TVulkanObject>>
		createSharedVulkanObject(TVulkanObject object, std::function<void(TVulkanObject)> deleter)
	{
			return std::make_shared<VulkanHandlerContainer<TVulkanObject>>(object, deleter);
	}
}

namespace CubA4::render::vulkan
{
	#define DEFINE_SHARED_VULKAN_CONTAINER(TVulkanObjectName) using s##TVulkanObjectName = \
	std::shared_ptr<CubA4::render::vulkan::util::VulkanHandlerContainer<TVulkanObjectName>>

	DEFINE_SHARED_VULKAN_CONTAINER(VkBuffer);
	DEFINE_SHARED_VULKAN_CONTAINER(VkImage);

	DEFINE_SHARED_VULKAN_CONTAINER(VkDescriptorSetLayout);
	DEFINE_SHARED_VULKAN_CONTAINER(VkDescriptorPool);
	DEFINE_SHARED_VULKAN_CONTAINER(VkDescriptorSet);
	#undef DEFINE_SHARED_VULKAN_CONTAINER
}
