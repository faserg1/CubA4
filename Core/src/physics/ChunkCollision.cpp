#include <physics/ChunkCollision.hpp>
#include <object/IBlock.hpp>
#include <stdexcept>
#include <future>
using namespace CubA4::physics;

ChunkCollision::ChunkCollision(CubA4::Core &core, std::shared_ptr<const CubA4::world::IChunk> chunk, btDiscreteDynamicsWorld &dynamicWorld) :
	core_(core), dynamicWorld_(dynamicWorld), chunkObject_(std::make_unique<btCollisionObject>()), chunkShape_(std::make_unique<btCompoundShape>())
{
	chunkObject_->setCollisionShape(chunkShape_.get());
	basis_.setRotation(btQuaternion(0.f, 0.f, 0.f));
	btTransform position;
	auto [x, y, z] = chunk->getChunkPos();
	position.setBasis(basis_);
	position.setOrigin(
		{
			static_cast<btScalar>(x * CubA4::world::ChunkSize),
			static_cast<btScalar>(y * CubA4::world::ChunkSize),
			static_cast<btScalar>(z * CubA4::world::ChunkSize)
		}
	);
	chunkObject_->setWorldTransform(position);
	// TODO: move to pool? or maybe in parent?
	chunkCompilation_ = std::async(std::launch::async, [this, chunk]()
	{
		initChunkCollision(chunk);
	});
	
	dynamicWorld.addCollisionObject(chunkObject_.get());
}

ChunkCollision::~ChunkCollision()
{
	dynamicWorld_.removeCollisionObject(chunkObject_.get());
}

void ChunkCollision::initChunkCollision(std::shared_ptr<const CubA4::world::IChunk> chunk)
{
	auto env = core_.getEnvironment();
	std::unordered_map<IdPair, std::unique_ptr<btConvexShape>, BlockAndBlockDataIdHash> blockShapes;
	auto &dataProvider = chunk->getDataProvider();
	
	for (uint32_t index = 0; index < CubA4::world::ChunkCube; index++)
	{
		// btBoxShape
		if (chunk->hasBlocksAt(index))
		{
			auto blocks = chunk->getBlocksAt(index);
			auto [x, y, z] = CubA4::world::posByIndex(index);
			for (auto &blockAt : blocks)
			{
				auto key = std::make_pair(blockAt.blockId, blockAt.dataId);
				btConvexShape *choosedShape = nullptr;
				if (auto it = blockShapes.find(key); it != blockShapes.end())
				{
					choosedShape = it->second.get();
				}
				else
				{
					auto blockStorage = dataProvider.getBlockDataStorage(blockAt.blockId);
					auto block = env->getObjectT<CubA4::object::IBlock>(blockAt.blockId);
					auto data = blockStorage->get(blockAt.dataId);
					auto &def = block->getPhysicsDefinition();
					auto shape = createByDefinition(def, *data);
					choosedShape = shape.get();
					blockShapes.insert(std::make_pair(key, std::move(shape)));
				}
				if (choosedShape)
				{
					btTransform transform;
					transform.setBasis(basis_);
					transform.setOrigin({static_cast<btScalar>(x + 0.5f), static_cast<btScalar>(y+ 0.5f), static_cast<btScalar>(z+ 0.5f)});
					chunkShape_->addChildShape(transform, choosedShape);
				}
			}
		}
	}
	blockShapes_ = std::move(blockShapes);
}

std::unique_ptr<btConvexShape> ChunkCollision::createByDefinition(const CubA4::physics::IBlockPhysicsDefinition &def, const CubA4::world::BlockData &data)
{
	auto shape = def.getShape(data);
	switch (shape)
	{
		case BlockShape::Box:
		{
			auto box = std::make_unique<btBoxShape>(btVector3{0.5, 0.5, 0.5});
			return box;
		}
		
	}
	throw std::runtime_error("Unknow collision shape");
	return {};
}