#ifndef RENDERGAMEHANDLER_HPP
#define RENDERGAMEHANDLER_HPP

#include <memory>
#include <game/IGameSubscriber.hpp>
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
				public virtual CubA4::core::game::IGameSubscriber
			{
			public:
				explicit RenderGameHandler();
				~RenderGameHandler();

				void setGame(std::shared_ptr<const CubA4::core::game::IGame> game);
				void worldChanged(std::shared_ptr<CubA4::mod::world::IWorld> newWorld) override;
			protected:
			private:
				std::unique_ptr<CubA4::core::util::ISubscription> gameSubscription_;
			};
		}
	}
}

#endif // RENDERGAMEHANDLER_HPP