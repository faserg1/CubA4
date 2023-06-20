#include <world/data/DataProvider.hpp>
using namespace CubA4::world;

DataProvider::DataProvider()
{
	
}

DataProvider::~DataProvider()
{
	
}

BlockDataStorage &DataProvider::getBlockDataStorage(int64_t blockId)
{
    if (auto it = blockDataStorages_.find(blockId); it != blockDataStorages_.end())
        return *it->second.get();
    auto storage = std::make_unique<BlockDataStorage>();
    auto *ptr = storage.get();
    blockDataStorages_.insert(std::make_pair(blockId, std::move(storage)));
    return *ptr;
}

const BlockDataStorage *DataProvider::getBlockDataStorage(int64_t blockId) const
{
    if (auto it = blockDataStorages_.find(blockId); it != blockDataStorages_.end())
        return it->second.get();
    return nullptr;
}