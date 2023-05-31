#pragma once

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
			void init(std::shared_ptr<const info::IApplicationInfo> info, std::shared_ptr<const ICore> core) override;
			void destroy() override;
			std::string getRenderEngineId() const override;
			std::shared_ptr<engine::IRenderEngine> getRenderEngine() override;
			std::shared_ptr<config::IRenderConfig> getRenderConfig() const override;
			uint32_t getSDLWindowFlags() const override;
		private:
			std::shared_ptr<const info::IApplicationInfo> info_;
			std::shared_ptr<config::IRenderConfig> config_;
			std::shared_ptr<const ICore> core_;
			std::shared_ptr<engine::IRenderEngine> engine_;
		};
	}
}
