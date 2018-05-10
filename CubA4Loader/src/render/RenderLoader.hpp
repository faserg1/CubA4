#ifndef RENDER_LOADER_HPP
#define RENDER_LOADER_HPP

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
			RenderLoader();
			~RenderLoader();

			std::vector<IRenderInfo *> getRenderInfoCollection();
			void setCurrentRenderInfo(IRenderInfo *renderInfo);
			IRenderInfo *getCurrentRenderInfo();
		};
	}
}

#endif // RENDER_LOADER_HPP