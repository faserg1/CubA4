#ifndef RENDERGAMEHANDLER_HPP
#define RENDERGAMEHANDLER_HPP

#include <memory>
#include <game/IGameSubscriber.hpp>
#include <world/IWorldSubscriber.hpp>
#include <util/ISubscription.hpp>

namespace CubA4
{
	namespace core
	{
		namespace game
		{
			class IGame;
		}
	}

	namespace render
	{
		namespace engine
		{
			class RenderGameHandler :
				public virtual CubA4::core::game::IGameSubscriber,
				public virtual CubA4::mod::world::IWorldSubscriber
			{
			public:
				explicit RenderGameHandler();
				~RenderGameHandler();

				void setGame(std::shared_ptr<const CubA4::core::game::IGame> game);
				void worldChanged(std::shared_ptr<const CubA4::mod::world::IWorld> newWorld) override;
			protected:
			private:
				std::unique_ptr<CubA4::core::util::ISubscription> gameSubscription_;
				std::unique_ptr<CubA4::core::util::ISubscription> worldSubscription_;
				std::shared_ptr<const CubA4::mod::world::IWorld> currentWorld_;
			private:
				void recompileWorld();
			};
		}
	}
}

#endif // RENDERGAMEHANDLER_HPP
