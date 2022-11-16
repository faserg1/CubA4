#pragma once

#include <memory>
#include <system/IStartup.hpp>
#include <game/Game.hpp>

namespace CubA4::system
{
	class Startup :
		public virtual IStartup
	{
	public:
		explicit Startup(std::weak_ptr<const ICore> core);
		~Startup();

		void load(system::IAppCallback &appCallback) override;

		void setup() override;
		void shutdown() override;

		void run() override;
		void stop() override;

		std::shared_ptr<CubA4::game::IGame> getGame() const override;
	protected:
		void loadConfigs();
		void saveConfigs();

		void initMods();
		void unloadMods();

		void initGame();
		void destroyGame();
	private:
		const std::weak_ptr<const ICore> core_;
		system::IAppCallback *appCallback_;
		std::shared_ptr<mod::IModLoader> modLoader_;
		std::shared_ptr<CubA4::game::Game> game_;
	};
}
