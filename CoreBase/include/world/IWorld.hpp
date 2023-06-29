#pragma once

#include <string>
#include <vector>
#include <world/IChunk.hpp>
#include <world/IWorldDefinition.hpp>
#include <world/IWorldSubscriber.hpp>
#include <object/IObject.hpp>
#include <object/IBlock.hpp>
#include <util/ISubscription.hpp>

namespace CubA4::world
{
	class IWorld :
		public virtual CubA4::object::IObject
	{
	public:
		virtual ~IWorld() = default;

		virtual std::unique_ptr<CubA4::util::ISubscription> subscribe(CubA4::world::IWorldSubscriber *subscriber) const = 0;

		// TODO: [OOKAMI] Test the chunk range feature. Delete function later
		virtual void test(std::vector<std::shared_ptr<const object::IBlock>> blocks) = 0;

		virtual std::shared_ptr<const CubA4::world::IWorldDefinition> getWorldDefinition() const = 0;
		virtual std::vector<std::shared_ptr<const IChunk>> getChunks() const = 0;
	protected:
		explicit IWorld() = default;
	};
}
