#pragma once

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
			class IGame;

			class IGameSubscriber
			{
			public:
				virtual void worldChanged(std::shared_ptr<const CubA4::mod::world::IWorld> newWorld) = 0;
			protected:
				explicit IGameSubscriber() = default;
				virtual ~IGameSubscriber() = default;
			private:
			};
		}
	}
}
