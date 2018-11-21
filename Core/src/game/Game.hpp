#ifndef GAME_HPP
#define GAME_HPP

#include <game/IGame.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include "../util/SubscriptionHelper.hpp"

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

				std::unique_ptr<CubA4::core::util::ISubscription> subscribe(IGameSubscriber *subscriber) const override;

				void run();
				void stop();
				void setupEnvironment(std::shared_ptr<system::Environment> env);
			protected:
			private:
				std::thread gameThread_;
				std::atomic_bool runGameLoop_;
				std::shared_ptr<system::Environment> env_;
				mutable CubA4::core::util::SubscriptionHelper<CubA4::core::game::IGameSubscriber> subscriptionHelper_;
			private:
				void loop();
			};
		}
	}
}

#endif // GAME_HPP
