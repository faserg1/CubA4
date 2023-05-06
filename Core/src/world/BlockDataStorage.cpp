#include <world/BlockDataStorage.hpp>
using namespace CubA4::world;

BlockDataStorage::BlockDataStorage()
{
	
}

BlockDataStorage::~BlockDataStorage()
{
	
}

std::shared_ptr<BlockData> BlockDataStorage::getOrAdd(const BlockData &data)
{
    if (auto ptr = find(data))
        return ptr;
    return add(data);
}

std::shared_ptr<BlockData> BlockDataStorage::modOrAdd(uint64_t id, const BlockData &data)
{
    if (auto ptr = mod(id, data))
        return ptr;
    return add(data);
}

std::shared_ptr<BlockData> BlockDataStorage::get(uint64_t id) const
{
    auto it = std::find_if(dataStorage_.begin(), dataStorage_.end(), [id](const auto &data)
    {
        return data->id == id;
    });
    if (it == dataStorage_.end())
        return {};
    return *it;
}

bool BlockDataStorage::remove(uint64_t id)
{
    auto it = std::find_if(dataStorage_.begin(), dataStorage_.end(), [id](const auto &data)
    {
        return data->id == id;
    });
    if (it == dataStorage_.end())
        return false;
    dataStorage_.erase(it);
    return true;
}

const BlockDataStorage::Storage &BlockDataStorage::getStorage() const
{
    return dataStorage_;
}

std::shared_ptr<BlockData> BlockDataStorage::add(BlockData data)
{
    data.id = idAllocator_++;
    auto ptr = std::make_shared<BlockData>(data);
    dataStorage_.insert(ptr);
    return ptr;
}

std::shared_ptr<BlockData> BlockDataStorage::mod(uint64_t id, const BlockData &data)
{
    auto blockData = get(id);
    if (!blockData)
        return {};
    *blockData = data;
    blockData->id = id;
    return blockData;
}

std::shared_ptr<BlockData> BlockDataStorage::find(const BlockData &data) const
{
    auto compareFunc = [&data](const auto &dataPtr) {return (data <=> *dataPtr) == std::weak_ordering::equivalent;};
    if (auto it = std::find_if(dataStorage_.begin(), dataStorage_.end(), compareFunc); it != dataStorage_.end())
        return *it;
    return {};
}