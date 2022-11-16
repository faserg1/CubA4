#pragma once

#include <memory>
#include <system/IAppCallback.hpp>
#include <system/IStartup.hpp>
#include <ICore.hpp>
#include <engine/IRenderEngine.hpp>

namespace CubA4::app
{
	class AppStartup final
	{
	public:
		explicit AppStartup(CubA4::system::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core, 
			std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine);
		~AppStartup();
		AppStartup(const AppStartup&) = delete;
		AppStartup(AppStartup &&) = delete;

		void nextMainLoopIteration();
		void keyChanged(CubA4::game::controller::Button btn, CubA4::game::controller::BMods mods, bool pressed);
	protected:
	private:
		bool setup();
		void shutdown();

		bool setupGame();
		void shutdownGame();

		void run();
		void stop();

		void doSomeTestThings();
	private:
		CubA4::system::IAppCallback &appCallback_;
		std::weak_ptr<CubA4::ICore> core_;
		std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine_;
		std::shared_ptr<CubA4::system::IStartup> startup_;
	};
}

