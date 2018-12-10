#ifndef COREBASE_IGAME_HPP
#define COREBASE_IGAME_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace util
		{
			class ISubscription;
		}
	}

	namespace core
	{
		namespace game
		{
			class IGameSubscriber;

			class IGame
			{
			public:
				virtual std::unique_ptr<CubA4::core::util::ISubscription> subscribe(IGameSubscriber *subscriber) const = 0;
			protected:
				explicit IGame() = default;
				virtual ~IGame() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IGAME_HPP
