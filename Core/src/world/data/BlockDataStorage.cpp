#include <world/data/BlockDataStorage.hpp>
using namespace CubA4::world;

BlockDataStorage::BlockDataStorage()
{
	
}

BlockDataStorage::~BlockDataStorage()
{
	
}

std::shared_ptr<BlockData> BlockDataStorage::getOrAdd(const BlockData &data, bool usage)
{
    if (auto ptr = find(data))
        return ptr;
    return add(data);
}

std::shared_ptr<BlockData> BlockDataStorage::modOrAdd(uint64_t id, const BlockData &data, bool usage)
{
    remove(id);
    return getOrAdd(data);
}

std::shared_ptr<BlockData> BlockDataStorage::get(uint64_t id, bool usage) const
{
    auto it = storage_.find(id);
	if (it == storage_.end())
		return {};
	if (usage)
		it->second.second++;
	return it->second.first;
}

bool BlockDataStorage::remove(uint64_t id)
{
    auto it = storage_.find(id);
	if (it == storage_.end())
		return false;
	it->second.second--;
	if (it->second.second == 0)
		storage_.erase(it);
}

std::shared_ptr<BlockData> BlockDataStorage::add(BlockData data)
{
    data.id = idAllocator_++;
    auto ptr = std::make_shared<BlockData>(data);
    BlockUsage usage {ptr, 1};
	storage_.insert(std::make_pair(data.id, usage));
    return ptr;
}

std::shared_ptr<BlockData> BlockDataStorage::find(const BlockData &data) const
{
    auto compareFunc = [&data](const std::pair<decltype(BlockData::id), BlockUsage> &dataPair) {return (data <=> *dataPair.second.first) == std::weak_ordering::equivalent;};
    if (auto it = std::find_if(storage_.begin(), storage_.end(), compareFunc); it != storage_.end())
        return it->second.first;
    return {};
}