#pragma once

#include <functional>
#include <memory>
#include <system/IAppClientCallback.hpp>
#include <render/RenderLoader.hpp>
#include <window/Window.hpp>
#include "DebugOverlay.hpp"

namespace CubA4::app
{
	class AppStartup;

	class AppMain final :
		public virtual CubA4::system::IAppClientCallback
	{
	public:
		explicit AppMain(int argc, const char *const argv[]);
		~AppMain();

		int exec();

		std::function<std::shared_ptr<mod::IModLoader>()> getModLoaderFactory() const override;
		std::shared_ptr<const CubA4::info::IApplicationInfo> getApplicationInfo() const override;
		std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;
		const CubA4::render::IRenderInfo &getRenderInfo() const override;
		std::pair<bool, CubA4::game::controller::BMods> getButtonState(CubA4::game::controller::Button btn) const override;
		bool requestMouseCapture(bool enable) override;
	private:
		void loadRender();
		void unloadRender();
		bool createWindow();
		void initRenderEngine();
		void destroyRenderEngine();

		bool setup();
		void shutdown();

		void loop(AppStartup &startup);
		void sdlEventsHandle(AppStartup &startup);
	private:
		bool running_;
		std::shared_ptr<CubA4::ICore> core_;
		std::shared_ptr<CubA4::info::IApplicationInfo> info_;
		std::shared_ptr<CubA4::render::RenderLoader> renderLoader_;
		std::shared_ptr<CubA4::window::Window> window_;

		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;

		std::unique_ptr<DebugOverlay> debugOverlay_;
	};
}
