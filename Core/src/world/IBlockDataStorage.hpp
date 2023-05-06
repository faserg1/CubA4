#pragma once

#include <set>
#include <memory>
#include <world/BlockData.hpp>

namespace CubA4::world
{
	
	class IBlockDataStorage
	{
	public:
		using Storage = std::set<std::shared_ptr<BlockData>>;

		/** Find the equivalent data */
		virtual std::shared_ptr<BlockData> getOrAdd(const BlockData &data) = 0;
		virtual std::shared_ptr<BlockData> modOrAdd(uint64_t id, const BlockData &data) = 0;
		virtual std::shared_ptr<BlockData> get(uint64_t id) const = 0;
		virtual bool remove(uint64_t id) = 0;

		virtual const Storage &getStorage() const = 0;
	public:
		virtual ~IBlockDataStorage() = default;
	protected:
		explicit IBlockDataStorage() = default;
	};
}
