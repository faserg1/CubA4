#ifndef CUBA4LOADER_CUBA4MAIN_HPP
#define CUBA4LOADER_CUBA4MAIN_HPP

#include <functional>
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
		class AppStartup;

		class AppMain final :
			public virtual CubA4::core::system::IAppCallback
		{
		public:
			explicit AppMain(int argc, const char *const argv[]);
			~AppMain();

			int exec();

			std::function<std::shared_ptr<mod::IModLoader>()> getModLoaderFactory() const override;
			std::shared_ptr<const CubA4::core::info::IApplicationInfo> getApplicationInfo() const override;
			std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;
			const CubA4::render::IRenderInfo &getRenderInfo() const override;
		private:
			void loadRender();
			void unloadRender();
			bool createWindow();
			void initRender();
			void destroyRender();

			bool setup();
			void shutdown();

			void loop(AppStartup &startup);
		private:
			bool running_;
			std::shared_ptr<CubA4::core::ICore> core_;
			std::shared_ptr<CubA4::core::info::IApplicationInfo> info_;
			std::shared_ptr<CubA4::render::RenderLoader> renderLoader_;
			std::shared_ptr<CubA4::window::Window> window_;

			std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;
		};
	}
}

#endif // CUBA4LOADER_CUBA4MAIN_HPP
