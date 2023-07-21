#pragma once

#include <memory>
#include <world/IWorld.hpp>

namespace CubA4::game
{
	class IGameSubscriber
	{
	public:
		virtual void onGameReady() {};
		virtual void worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld) {};
		virtual void loadedChunksChanged(const std::vector<CubA4::world::ChunkPos> &chunksPositions) {};
		virtual void activeChunksChanged(const std::vector<CubA4::world::ChunkPos> &chunksPositions) {};
	protected:
		explicit IGameSubscriber() = default;
		virtual ~IGameSubscriber() = default;
	private:
	};
}

