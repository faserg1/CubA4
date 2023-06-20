#pragma once

#include <memory>
#include <world/data/BlockData.hpp>

namespace CubA4::world
{
	
	class IBlockDataStorage
	{
	public:
		/** Find the equivalent data */
		virtual std::shared_ptr<BlockData> getOrAdd(const BlockData &data, bool usage = false) = 0;
		virtual std::shared_ptr<BlockData> modOrAdd(uint64_t id, const BlockData &data, bool usage = false) = 0;
		virtual std::shared_ptr<BlockData> get(uint64_t id, bool usage = false) const = 0;
		virtual bool remove(uint64_t id) = 0;
	public:
		virtual ~IBlockDataStorage() = default;
	protected:
		explicit IBlockDataStorage() = default;
	};
}
