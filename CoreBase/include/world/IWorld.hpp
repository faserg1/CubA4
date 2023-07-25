#pragma once

#include <string>
#include <vector>
#include <world/IChunk.hpp>
#include <world/IDimension.hpp>
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

		virtual std::shared_ptr<const CubA4::world::IWorldDefinition> getWorldDefinition() const = 0;
		virtual std::vector<std::shared_ptr<const IDimension>> getDimensions() const = 0;
		virtual std::shared_ptr<const IDimension> findDimension(std::string id) const = 0;
	protected:
		explicit IWorld() = default;
	};
}
