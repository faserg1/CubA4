#ifndef VULKAN_INFO_HPP
#define VULKAN_INFO_HPP

#include <RenderInfo.hpp>

namespace CubA4
{
	namespace render
	{
		class VulkanInfo : public virtual RenderInfo
		{
		public:
			VulkanInfo();
			~VulkanInfo();
			std::string getRenderEngineName() const override;
			RenderEngine *getRenderEngine() override;
		};
	}
}

#endif // VULKAN_INFO_HPP