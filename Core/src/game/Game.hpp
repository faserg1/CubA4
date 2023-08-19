#pragma once

#include <game/IGame.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <util/SubscriptionHelper.hpp>
#include <game/controller/Controller.hpp>
#include <core/Environment.hpp>

namespace CubA4
{
	class Core;
}

namespace CubA4::game
{
	class Game :
		public virtual IGame
	{
		friend class GameControl;
	public:
		explicit Game(CubA4::Core &core, CubA4::core::IAppCallback &appCallback);
		~Game();

		std::unique_ptr<CubA4::util::ISubscription> subscribe(IGameSubscriber *subscriber) const override;
		std::shared_ptr<const CubA4::game::controller::IController> getController() const override;
		std::shared_ptr<CubA4::game::controller::IController> getController() override;
		CubA4::object::IEntityRenderManager *getEntityRenderManager() const override;

		void run();
		void stop();
		void setupEnvironment(std::shared_ptr<core::Environment> env);
	protected:
	private:
		CubA4::Core &core_;
		CubA4::core::IAppCallback &appCallback_;
		std::atomic_bool runGameLoop_;
		const std::shared_ptr<controller::Controller> controller_;
		std::thread gameThread_;
		std::shared_ptr<core::Environment> env_;
		
		mutable CubA4::util::SubscriptionHelper<CubA4::game::IGameSubscriber> subscriptionHelper_;
	private:
		void loop();
		void iterate(float seconds);
		std::shared_ptr<controller::Controller> createController();
	};
}

