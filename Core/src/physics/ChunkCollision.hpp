#pragma once

#include <memory>
#include <world/IChunk.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <Core.hpp>
#include <future>

namespace CubA4::physics
{
	class IBlockPhysicsDefinition;

	class BlockAndBlockDataIdHash
	{
		using BlockId = CubA4::core::IIdentityiMap::IdType;
		using BlockDataId = decltype(CubA4::world::BlockData::id);
	public:
		size_t operator()(const std::pair<BlockId, BlockDataId> &pair) const
		{
			auto hash1 = std::hash<BlockId>{}(pair.first);
			auto hash2 = std::hash<BlockDataId>{}(pair.second);
	
			if (hash1 != hash2) {
				return hash1 ^ hash2;             
			}
			
			// If hash1 == hash2, their XOR is zero.
			return hash1;
		}
	};

	class ChunkCollision
	{
		using BlockId = CubA4::core::IIdentityiMap::IdType;
		using BlockDataId = decltype(CubA4::world::BlockData::id);
		using IdPair = std::pair<BlockId, BlockDataId>;
	public:
		ChunkCollision(CubA4::Core &core, std::shared_ptr<const CubA4::world::IChunk> chunk, btDiscreteDynamicsWorld &dynamicWorld);
		~ChunkCollision();

	private:
		void initChunkCollision(std::shared_ptr<const CubA4::world::IChunk> chunk);
		std::unique_ptr<btConvexShape> createByDefinition(const CubA4::physics::IBlockPhysicsDefinition &def, const CubA4::world::BlockData &data);
	private:
		CubA4::Core &core_;
		btDiscreteDynamicsWorld &dynamicWorld_;
		std::unique_ptr<btCollisionObject> chunkObject_;
		std::unique_ptr<btCompoundShape> chunkShape_;
		std::unordered_map<IdPair, std::unique_ptr<btConvexShape>, BlockAndBlockDataIdHash> blockShapes_;
		std::future<void> chunkCompilation_;

		btMatrix3x3 basis_;
	};
}