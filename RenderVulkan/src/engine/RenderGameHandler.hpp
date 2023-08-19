#pragma once

#include <memory>
#include <limits>
#include <game/IGame.hpp>
#include <game/IGameSubscriber.hpp>
#include <world/IWorld.hpp>
#include <world/IWorldSubscriber.hpp>
#include <world/IDimensionSubscriber.hpp>
#include <util/ISubscription.hpp>
#include <engine/pipeline/IRenderEngineWorldPipeline.hpp>
#include <engine/pipeline/IRenderEngineEntityPipeline.hpp>
#include <engine/pipeline/IRenderEntitySubscriber.hpp>

namespace CubA4
{
	class ICore;
}

namespace CubA4::render::engine
{

	class RenderGameHandler :
		public virtual CubA4::game::IGameSubscriber,
		public virtual CubA4::world::IWorldSubscriber,
		public virtual CubA4::world::IDimensionSubscriber,
		public virtual CubA4::render::engine::pipeline::IRenderEntitySubscriber
	{
		using IdType = CubA4::core::IIdentityiMap::IdType;
	public:
		explicit RenderGameHandler(std::shared_ptr<const CubA4::ICore> core,
			std::shared_ptr<pipeline::IRenderEngineWorldPipeline> worldUpdater,
			std::shared_ptr<pipeline::IRenderEngineEntityPipeline> entityUpdater);
		~RenderGameHandler();

		void setGame(std::shared_ptr<const CubA4::game::IGame> game);
		void worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld,
			std::shared_ptr<const CubA4::world::IDimension> newDimension) override;

		void onActiveChunksUpdated() override;
		void onLoadedChunksUpdated() override;

		void onEntityAdded(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) override;
		void onEntityUpdated(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) override;
		void onEntityRemoved(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) override;
	protected:
	private:
		const std::shared_ptr<const CubA4::ICore> core_;
		const std::shared_ptr<pipeline::IRenderEngineWorldPipeline> worldUpdater_;
		const std::shared_ptr<pipeline::IRenderEngineEntityPipeline> entityUpdater_;
		std::unique_ptr<CubA4::util::ISubscription> gameSubscription_;
		std::unique_ptr<CubA4::util::ISubscription> entitySubscription_;
		std::unique_ptr<CubA4::util::ISubscription> worldSubscription_;
		std::unique_ptr<CubA4::util::ISubscription> dimensionSubscription_;
		std::shared_ptr<const CubA4::world::IWorld> currentWorld_;
		std::shared_ptr<const CubA4::world::IDimension> currentDimension_;

		IdType currentWorldId_ = std::numeric_limits<IdType>::max();
		IdType currentDimensionId_ = std::numeric_limits<IdType>::max();
		
	private:
		void recompileWorld();
	};
}
