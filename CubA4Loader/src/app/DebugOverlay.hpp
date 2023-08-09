#pragma once

#include <memory>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			class IRenderEngine;

			namespace debug
			{
				class IRenderDebugCollection;
			}
		}

		namespace ui
		{
			class IRenderUIManager;
			class IComponentFactory;
			class IText;
			class IFrame;
		}
	}

	namespace app
	{
		class DebugOverlay
		{
		public:
			DebugOverlay(std::shared_ptr<CubA4::render::engine::IRenderEngine> renderEngine);

			void update();
			void toggleVisibility();
		private:
			std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine_;
			std::weak_ptr<CubA4::render::ui::IRenderUIManager> renderUiManager_;

			std::shared_ptr<CubA4::render::ui::IFrame> debugOverlay_;
			std::shared_ptr<CubA4::render::ui::IText> fpsLabel_;

			std::vector<std::shared_ptr<CubA4::render::engine::debug::IRenderDebugCollection>> worldLines_;
		};
	}
}