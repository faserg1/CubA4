#ifndef CUBA4MAIN_HPP
#define CUBA4MAIN_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace info
		{
			class IApplicationInfo;
		}
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
			explicit AppMain(int argc, const char *const argv[]);

			int exec();
		private:
			void loadRender();
			void unloadRender();
			bool createWindow();
			void initRender();
			void destroyRender();
			void loop();

			bool running_;
			std::shared_ptr<CubA4::core::ICore> core_;
			std::shared_ptr<CubA4::core::info::IApplicationInfo> info_;
			std::shared_ptr<CubA4::render::RenderLoader> renderLoader_;
			std::shared_ptr<CubA4::window::Window> window_;
		};
	}
}

#endif // CUBA4MAIN_HPP