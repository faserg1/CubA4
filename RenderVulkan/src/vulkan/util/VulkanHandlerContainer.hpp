#ifndef RENDERVULKAN_VULKANHANDLERCONTAINER_HPP
#define RENDERVULKAN_VULKANHANDLERCONTAINER_HPP

#include <memory>
#include <functional>
#include <vulkan/vulkan.h>
#include <iostream>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace util
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

			#define DEFINE_SHARED_VULKAN_CONTAINER(TVulkanObjectName) using s##TVulkanObjectName = \
				std::shared_ptr<util::VulkanHandlerContainer<TVulkanObjectName>>
			DEFINE_SHARED_VULKAN_CONTAINER(VkDescriptorSetLayout);
			#undef DEFINE_SHARED_VULKAN_CONTAINER
		}
	}
}

#endif // RENDERVULKAN_VULKANHANDLERCONTAINER_HPP
