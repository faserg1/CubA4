#ifndef VULKAN_INFO_HPP
#define VULKAN_INFO_HPP

#include <IRenderInfo.hpp>

namespace CubA4
{
	namespace render
	{
		class VulkanInfo :
			public virtual IRenderInfo
		{
		public:
			VulkanInfo();
			~VulkanInfo();
			std::string getRenderEngineId() const override;
			IRenderEngine *getRenderEngine() override;
			int64_t getSDLWindowFlags() const override;
		};
	}
}

#endif // VULKAN_INFO_HPP