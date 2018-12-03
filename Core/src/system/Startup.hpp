#ifndef STARTUP_HPP
#define STARTUP_HPP

#include <memory>
#include <system/IStartup.hpp>

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace core
	{
		class ICore;

		namespace game
		{
			class Game;
		}

		namespace system
		{
			class IAppCallback;

			class Startup :
				public virtual IStartup
			{
			public:
				explicit Startup(std::weak_ptr<const ICore> core);
				~Startup();

				void load(system::IAppCallback &appCallback) override;
				void unload() override;

				void setup() override;
				void shutdown() override;

				void run() override;
				void stop() override;

				std::shared_ptr<CubA4::core::game::IGame> getGame() const override;
			protected:
				void initMods();
				void unloadMods();

				void initGame();
				void destroyGame();
			private:
				const std::weak_ptr<const ICore> core_;
				system::IAppCallback *appCallback_;
				std::shared_ptr<mod::IModLoader> modLoader_;
				std::shared_ptr<CubA4::core::game::Game> game_;
			};
		}
	}
}

#endif // STARTUP_HPP
