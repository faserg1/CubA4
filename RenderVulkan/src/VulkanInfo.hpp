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
			void init(std::shared_ptr<const core::info::IApplicationInfo> info, std::shared_ptr<core::logging::ILogger> logger) override;
			void destroy() override;
			std::string getRenderEngineId() const override;
			std::shared_ptr<engine::IRenderEngine> getRenderEngine() override;
			int64_t getSDLWindowFlags() const override;
		private:
			std::shared_ptr<const core::info::IApplicationInfo> info_;
			std::shared_ptr<core::logging::ILogger> logger_;
			std::shared_ptr<engine::IRenderEngine> engine_;
		};
	}
}

#endif // VULKAN_INFO_HPP