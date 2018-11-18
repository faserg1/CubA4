#ifndef GAME_HPP
#define GAME_HPP

#include <game/IGame.hpp>
#include <thread>
#include <atomic>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class Environment;
		}

		namespace game
		{
			class Game :
				public virtual IGame
			{
			public:
				explicit Game();
				~Game();

				void run();
				void stop();
				void setupEnvironment(std::shared_ptr<system::Environment> env);
			protected:
			private:
				std::thread gameThread_;
				std::atomic_bool runGameLoop_;
				std::shared_ptr<system::Environment> env_;
			private:
				void loop();
			};
		}
	}
}

#endif // GAME_HPP
