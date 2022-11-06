#pragma once

#include <game/IGame.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <util/SubscriptionHelper.hpp>
#include <system/Environment.hpp>

namespace CubA4::game
{
	class Game :
		public virtual IGame
	{
	public:
		explicit Game();
		~Game();

		std::unique_ptr<CubA4::util::ISubscription> subscribe(IGameSubscriber *subscriber) const override;

		void run();
		void stop();
		void setupEnvironment(std::shared_ptr<system::Environment> env);
	protected:
	private:
		std::thread gameThread_;
		std::atomic_bool runGameLoop_;
		std::shared_ptr<system::Environment> env_;
		mutable CubA4::util::SubscriptionHelper<CubA4::game::IGameSubscriber> subscriptionHelper_;
	private:
		void loop();
	};
}

