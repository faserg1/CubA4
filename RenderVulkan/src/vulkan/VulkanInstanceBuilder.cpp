#include "./VulkanInstanceBuilder.hpp"
#include <vulkan/vulkan.h>
#include <SDL_vulkan.h>
using namespace CubA4::render::vulkan;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			struct VulkanInstanceBuilderData
			{
				VkApplicationInfo appInfo;
				VkInstanceCreateInfo instanceInfo;
			};
		}
	}
}

VulkanInstanceBuilder::VulkanInstanceBuilder() :
	data_(std::make_shared<VulkanInstanceBuilderData>())
{
	memset(&(*data_), 0, sizeof(VulkanInstanceBuilderData));
	data_->instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	data_->instanceInfo.pApplicationInfo = &data_->appInfo;
	data_->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	fillAppInfo();
}

VulkanInstanceBuilder::~VulkanInstanceBuilder()
{
	
}

std::shared_ptr<const VulkanInstance> VulkanInstanceBuilder::build()
{
	return std::shared_ptr<const VulkanInstance>();
}

void VulkanInstanceBuilder::fillAppInfo()
{
	// TDOO: [OOKAMI] Получить информацию о приложении из вне.
	data_->appInfo.pApplicationName = "CubA4 Loader";
	data_->appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	data_->appInfo.apiVersion = VK_MAKE_VERSION(1, 1, 0);
}

