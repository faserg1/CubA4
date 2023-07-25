#pragma once

#include <Core.hpp>
#include <world/IDimension.hpp>
#include <world/Chunk.hpp>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <util/ChunkPosHash.hpp>
#include <util/SubscriptionHelper.hpp>

namespace CubA4::world
{
	class Dimension : public virtual IDimension
	{
		friend class WorldControl;
	public:
		Dimension(Core &core, const CubA4::world::IDimensionDescription &description);

		IdType getId() const override;
		std::wstring getName() const override;

		std::unique_ptr<CubA4::util::ISubscription> subscribe(CubA4::world::IDimensionSubscriber *subscriber) const override;

		const CubA4::world::IDimensionDescription &getDimensionDescription() const override;
		std::vector<std::shared_ptr<const IChunk>> getChunks() const override;

		std::vector<CubA4::world::ChunkPos> getLoadedChunks() override;
		std::vector<CubA4::world::ChunkPos> getActiveChunks() override;

		void onChunkLoaded(std::shared_ptr<Chunk> chunk);
		void onChunkActived(CubA4::world::ChunkPos position);

		void onChunkUnload(CubA4::world::ChunkPos position);
		void onChunkDeactivated(CubA4::world::ChunkPos position);

		std::shared_ptr<const IChunk> findChunk(CubA4::world::ChunkPos pos) const override;
		std::shared_ptr<Chunk> findChunk(CubA4::world::ChunkPos pos);
	private:
		Core &core_;
		const CubA4::world::IDimensionDescription &description_;
		// remove friend and share?
		mutable CubA4::util::SubscriptionHelper<CubA4::world::IDimensionSubscriber> subscriptionHelper_;

		std::unordered_map<const CubA4::world::ChunkPos, std::shared_ptr<CubA4::world::Chunk>, CubA4::util::ChunkPosHash> loadedChunks_;
		std::unordered_set<CubA4::world::ChunkPos, CubA4::util::ChunkPosHash> activeChunks_;
	};
}



