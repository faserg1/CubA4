#pragma once

#include <world/IWorldControl.hpp>
#include <world/Dimension.hpp>
#include <world/World.hpp>
#include <world/ChunkAssembler.hpp>

namespace CubA4::world
{
	class WorldControl : public virtual IWorldControl
	{
	public:
		WorldControl(Core &core);
		// TODO: return couroutine?
		void requestChanges(const ChunkModificationCollection& modifications, const std::string &targetDimension) override;

		void setCurrentWorld(std::shared_ptr<World> world);
		std::shared_ptr<IWorld> getCurrentWorld() override;
		std::shared_ptr<const IWorld> getCurrentWorld() const override;
	private:
		// static?
		bool testLocal(std::shared_ptr<Chunk> chunk, const ChunkBModification& modification) const;
	private:
		Core &core_;
		std::unique_ptr<ChunkAssembler> chunkAssembler_;
		std::shared_ptr<World> currentWorld_;
		// dim?
	};
}