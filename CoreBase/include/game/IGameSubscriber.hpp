#ifndef IGAMESUBSCRIBER_HPP
#define IGAMESUBSCRIBER_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorld;
		}
	}

	namespace core
	{
		namespace game
		{
			class IGameSubscriber
			{
			public:
				virtual void worldChanged(std::shared_ptr<CubA4::mod::world::IWorld> newWorld) = 0;
			protected:
				explicit IGameSubscriber() = default;
				virtual ~IGameSubscriber() = default;
			private:
			};
		}
	}
}

#endif // IGAMESUBSCRIBER_HPP
