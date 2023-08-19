#pragma once

#include <memory>
#include <core/IAppCallback.hpp>
#include <core/IStartup.hpp>
#include <ICore.hpp>
#include <engine/IRenderEngine.hpp>
#include <engine/world/ICamera.hpp>

namespace CubA4::app
{
	class AppStartup final
	{
	public:
		explicit AppStartup(CubA4::core::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core, 
			std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine);
		~AppStartup();
		AppStartup(const AppStartup&) = delete;
		AppStartup(AppStartup &&) = delete;

		void nextMainLoopIteration(double delta);
		void keyChanged(CubA4::game::controller::Button btn, CubA4::game::controller::BMods mods, bool pressed);
		void mouseMove(int32_t x, int32_t y, bool relative);

		std::shared_ptr<CubA4::core::IStartup> getSystemStartup();
	protected:
	private:
		bool setup();
		void shutdown();

		bool setupGame();
		void shutdownGame();

		void run();
		void stop();

		void doSomeTestThings(double delta);
	private:
		CubA4::core::IAppCallback &appCallback_;
		std::weak_ptr<CubA4::ICore> core_;
		std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine_;
		std::shared_ptr<CubA4::core::IStartup> startup_;

		// test
		std::shared_ptr<CubA4::render::engine::world::ICamera> camera_;
	};
}

