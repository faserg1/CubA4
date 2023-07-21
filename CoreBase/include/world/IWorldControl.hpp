#pragma once

#include <world/ChunkBModification.hpp>
#include <world/IWorld.hpp>
#include <vector>

namespace CubA4::world
{
	/// @brief This should also look for active and loaded chunks
	class IWorldControl
	{
	public:
		virtual ~IWorldControl() = default;
		using ChunkModificationCollection = std::vector<ChunkBModification>;
		// TODO: return couroutine?
		virtual void requestChanges(const ChunkModificationCollection& modifications, const std::string &targetDimension) = 0;
		virtual std::shared_ptr<IWorld> getCurrentWorld() = 0;
		virtual std::shared_ptr<const IWorld> getCurrentWorld() const = 0;
	protected:
		IWorldControl() = default;
	};
}