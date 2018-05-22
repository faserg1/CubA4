#ifndef VULKANRENDERENGINE_HPP
#define VULKANRENDERENGINE_HPP

#include <engine/IRenderEngine.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanInstance;
		}

		namespace engine
		{
			class VulkanRenderEngine :
				public virtual IRenderEngine
			{
			public:
				explicit VulkanRenderEngine();
				~VulkanRenderEngine();

				void init() override;
				void destroy() override;
			protected:
			private:
				std::shared_ptr<const vulkan::VulkanInstance> instance_;
			};
		}
	}
}

#endif // VULKANRENDERENGINE_HPP
