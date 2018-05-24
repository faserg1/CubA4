#ifndef VULKANRENDERENGINE_HPP
#define VULKANRENDERENGINE_HPP

#include <engine/IRenderEngine.hpp>
#include <vector>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IApplicationInfo;
		}
	}

	namespace render
	{
		namespace vulkan
		{
			class VulkanInstance;
			class VulkanInstanceBuilder;
			namespace addon
			{
				class VulkanInstanceAddon;
			}
		}

		namespace engine
		{
			class VulkanRenderEngine :
				public virtual IRenderEngine
			{
			public:
				explicit VulkanRenderEngine(std::shared_ptr<const core::info::IApplicationInfo> info);
				~VulkanRenderEngine();

				void init(std::shared_ptr<window::IWindow> window) override;
				void destroy() override;
			protected:
			private:
				std::shared_ptr<const core::info::IApplicationInfo> info_;
				std::shared_ptr<vulkan::VulkanInstanceBuilder> instanceBuilder_;
				std::shared_ptr<const vulkan::VulkanInstance> instance_;
				std::vector<std::shared_ptr<vulkan::addon::VulkanInstanceAddon>> addons_;
			};
		}
	}
}

#endif // VULKANRENDERENGINE_HPP
