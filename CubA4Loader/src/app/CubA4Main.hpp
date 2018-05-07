#ifndef CUBA4MAIN_HPP
#define CUBA4MAIN_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class Core;
	}

	namespace render
	{
		class RenderLoader;
	}

	namespace window
	{
		class Window;
	}

	namespace app
	{
		class AppMain
		{
		public:
			explicit AppMain();

			int exec();
		private:
			void loadRender();
			void createWindow();
			void initRender();
			void loop();

			bool running_;
			std::shared_ptr<CubA4::core::Core> core_;
			std::shared_ptr<CubA4::render::RenderLoader> renderLoader_;
			std::shared_ptr<CubA4::window::Window> window_;
		};
	}
}

#endif // CUBA4MAIN_HPP