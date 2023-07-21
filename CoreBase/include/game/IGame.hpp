#pragma once

#include <memory>
#include <util/ISubscription.hpp>
#include <game/controller/IController.hpp>

namespace CubA4::game
{
	class IGameSubscriber;

	class IGame
	{
	public:
		virtual std::unique_ptr<CubA4::util::ISubscription> subscribe(IGameSubscriber *subscriber) const = 0;
		virtual std::shared_ptr<const CubA4::game::controller::IController> getController() const = 0;
		virtual std::shared_ptr<CubA4::game::controller::IController> getController() = 0;
	protected:
		explicit IGame() = default;
		virtual ~IGame() = default;
	private:
	};
}
