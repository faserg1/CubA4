#pragma once

#include <memory>
#include <core/IStartup.hpp>
#include <game/Game.hpp>
#include <game/GameControl.hpp>
#include <Core.hpp>

namespace CubA4::core
{
	class Startup :
		public virtual IStartup
	{
	public:
		explicit Startup(std::shared_ptr<Core> core);
		~Startup();

		void load(core::IAppCallback &appCallback) override;

		void setup() override;
		void shutdown() override;

		void run() override;
		void stop() override;

		std::shared_ptr<CubA4::game::IGame> getGame() const override;

		CubA4::core::IAppCallback *getAppCallbacks();
	protected:
		void loadConfigs();
		void saveConfigs();

		void initMods();
		void unloadMods();

		void initGame();
		void destroyGame();

		void startMods();
		void stopMods();
	private:
		const std::weak_ptr<Core> core_;
		core::IAppCallback *appCallback_;
		std::shared_ptr<mod::IModLoader> modLoader_;
		std::shared_ptr<CubA4::game::Game> game_;
		std::unique_ptr<CubA4::game::GameControl> gameControl_;
	};
}
