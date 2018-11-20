#ifndef CUBA4MAIN_HPP
#define CUBA4MAIN_HPP

#include <memory>
#include <system/IAppCallback.hpp>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace info
		{
			class IApplicationInfo;
		}

		namespace logging
		{
			class ILoggerTagged;
		}
	}

	namespace mod
	{
		class ModLoader;
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
		class AppMain :
			public virtual CubA4::core::system::IAppCallback
		{
		public:
			explicit AppMain(int argc, const char *const argv[]);

			int exec();

			std::shared_ptr<mod::IModLoader> getModLoader() const override;
			std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;
			const CubA4::render::IRenderInfo &getRenderInfo() const override;
		private:
			void loadRender();
			void unloadRender();
			bool createWindow();
			void initRender();
			void destroyRender();

			bool setup();
			void unload();

			void run();
			void stop();

			void loop();

			bool running_;
			std::shared_ptr<CubA4::core::ICore> core_;
			std::shared_ptr<CubA4::core::info::IApplicationInfo> info_;
			std::shared_ptr<CubA4::render::RenderLoader> renderLoader_;
			std::shared_ptr<CubA4::window::Window> window_;

			std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;

			std::shared_ptr<CubA4::mod::ModLoader> modLoader_;
		};
	}
}

#endif // CUBA4MAIN_HPP