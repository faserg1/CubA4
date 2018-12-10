#ifndef CUBA4LOADER_RENDER_LOADER_HPP
#define CUBA4LOADER_RENDER_LOADER_HPP

#include <vector>
#include <memory>
#include <IRenderInfo.hpp>

namespace CubA4
{
	namespace render
	{
		class RenderLoader final
		{
			struct Private;
			const char *const importSymbolName_;
			std::shared_ptr<Private> data_;

			IRenderInfo *currentRenderInfo_;
		public:
			RenderLoader(std::string renderPath);
			~RenderLoader();

			std::vector<IRenderInfo *> getRenderInfoCollection();
			void setCurrentRenderInfo(IRenderInfo *renderInfo);
			IRenderInfo *getCurrentRenderInfo();
		};
	}
}

#endif // CUBA4LOADER_RENDER_LOADER_HPP