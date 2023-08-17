#pragma once

#include <string>
#include <vector>
#include <world/IChunk.hpp>
#include <world/GlobalPosition.hpp>
#include <world/IDimensionDescription.hpp>
#include <world/IDimensionSubscriber.hpp>
#include <object/IObject.hpp>
#include <object/IBlock.hpp>
#include <util/ISubscription.hpp>

namespace CubA4::world
{
	class IWorld;

	class IDimension :
		public virtual CubA4::object::IObject
	{
	public:
		virtual ~IDimension() = default;

		virtual std::unique_ptr<CubA4::util::ISubscription> subscribe(CubA4::world::IDimensionSubscriber *subscriber) const = 0;

		virtual const CubA4::world::IDimensionDescription &getDimensionDescription() const = 0;
		virtual std::vector<std::shared_ptr<const IChunk>> getChunks() const = 0;

		virtual std::vector<CubA4::world::ChunkPos> getLoadedChunks() = 0;
		virtual std::vector<CubA4::world::ChunkPos> getActiveChunks() = 0;

		virtual void rayTest(CubA4::world::GlobalPosition from, CubA4::world::GlobalPosition to) const = 0;

		virtual const IWorld &getWorld() const = 0;

		virtual std::shared_ptr<const IChunk> findChunk(CubA4::world::ChunkPos pos) const = 0;
	protected:
		explicit IDimension() = default;
	};
}
