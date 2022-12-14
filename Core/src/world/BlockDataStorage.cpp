#include <world/BlockDataStorage.hpp>
using namespace CubA4::world;

BlockDataStorage::BlockDataStorage()
{
	
}

BlockDataStorage::~BlockDataStorage()
{
	
}

std::shared_ptr<BlockData> BlockDataStorage::findOrAdd(BlockData data)
{
    if (auto ptr = find(data); ptr)
        return ptr;
    return add(data);
}

std::shared_ptr<BlockData> BlockDataStorage::find(BlockData data) const
{
    return {};
}

std::shared_ptr<BlockData> BlockDataStorage::get(uint64_t id) const
{
    return {};
}

bool BlockDataStorage::remove(uint64_t id)
{
    return false;
}

std::shared_ptr<BlockData> BlockDataStorage::add(BlockData data)
{
    return {};
}