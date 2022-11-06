#pragma once

#include <vector>
#include <memory>
#include <IRenderInfo.hpp>

namespace CubA4
{
	namespace system
	{
		class IRuntime;
	}

	namespace render
	{
		class RenderLoader final
		{
			struct Private;
		public:
			RenderLoader(std::string renderPath, std::shared_ptr<system::IRuntime> runtime);
			~RenderLoader();

			std::vector<IRenderInfo *> getRenderInfoCollection();
			void setCurrentRenderInfo(IRenderInfo *renderInfo);
			IRenderInfo *getCurrentRenderInfo();
		private:
			const char *const importSymbolName_;
			std::shared_ptr<Private> data_;
			IRenderInfo *currentRenderInfo_;
			const std::shared_ptr<system::IRuntime> runtime_;
		};
	}
}
