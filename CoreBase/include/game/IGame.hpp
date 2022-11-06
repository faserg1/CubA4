#pragma once

#include <memory>
#include <util/ISubscription.hpp>

namespace CubA4::game
{
	class IGameSubscriber;

	class IGame
	{
	public:
		virtual std::unique_ptr<CubA4::util::ISubscription> subscribe(IGameSubscriber *subscriber) const = 0;
	protected:
		explicit IGame() = default;
		virtual ~IGame() = default;
	private:
	};
}
