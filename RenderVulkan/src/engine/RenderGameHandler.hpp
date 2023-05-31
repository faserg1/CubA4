#pragma once

#include <memory>
#include <game/IGame.hpp>
#include <game/IGameSubscriber.hpp>
#include <world/IWorld.hpp>
#include <world/IWorldSubscriber.hpp>
#include <util/ISubscription.hpp>
#include <engine/pipeline/IRenderEngineWorldPipeline.hpp>


namespace CubA4::render::engine
{

	class RenderGameHandler :
		public virtual CubA4::game::IGameSubscriber,
		public virtual CubA4::world::IWorldSubscriber
	{
	public:
		explicit RenderGameHandler(std::shared_ptr<pipeline::IRenderEngineWorldPipeline> updater);
		~RenderGameHandler();

		void setGame(std::shared_ptr<const CubA4::game::IGame> game);
		void worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld) override;
	protected:
	private:
		const std::shared_ptr<pipeline::IRenderEngineWorldPipeline> updater_;
		std::unique_ptr<CubA4::util::ISubscription> gameSubscription_;
		std::unique_ptr<CubA4::util::ISubscription> worldSubscription_;
		std::shared_ptr<const CubA4::world::IWorld> currentWorld_;
	private:
		void recompileWorld();
	};
}
