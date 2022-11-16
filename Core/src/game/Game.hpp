#pragma once

#include <game/IGame.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <util/SubscriptionHelper.hpp>
#include <game/controller/Controller.hpp>
#include <system/Environment.hpp>

namespace CubA4::game
{
	class Game :
		public virtual IGame
	{
	public:
		explicit Game(CubA4::system::IAppCallback &appCallback);
		~Game();

		std::unique_ptr<CubA4::util::ISubscription> subscribe(IGameSubscriber *subscriber) const override;
		std::shared_ptr<const CubA4::game::controller::IController> getController() const override;
		std::shared_ptr<CubA4::game::controller::IController> getController() override;

		void run();
		void stop();
		void setupEnvironment(std::shared_ptr<system::Environment> env);
	protected:
	private:
		CubA4::system::IAppCallback &appCallback_;
		std::atomic_bool runGameLoop_;
		const std::shared_ptr<controller::Controller> controller_;
		std::thread gameThread_;
		std::shared_ptr<system::Environment> env_;
		
		mutable CubA4::util::SubscriptionHelper<CubA4::game::IGameSubscriber> subscriptionHelper_;
	private:
		void loop();
	};
}

