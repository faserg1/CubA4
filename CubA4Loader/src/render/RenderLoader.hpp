#ifndef RENDER_LOADER_HPP
#define RENDER_LOADER_HPP

#include <vector>
#include <RenderInfo.hpp>

namespace CubA4
{
	namespace render
	{
		class RenderLoader final
		{
			struct Private;
			const char *const importSymbolName;
			Private *data_;

			RenderInfo *currentRenderInfo_;
		public:
			RenderLoader();
			~RenderLoader();

			std::vector<RenderInfo *> getRenderInfoCollection();
			void setCurrentRenderInfo(RenderInfo *renderInfo);
			RenderInfo *getCurrentRenderInfo();
		};
	}
}

#endif // RENDER_LOADER_HPP