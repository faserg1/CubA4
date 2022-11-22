#pragma once

#include <memory>
#include <cstdint>
#include <world/Position.hpp>

namespace CubA4::world
{
	class IChunkBIterator
	{
	public:
		virtual ~IChunkBIterator() = default;

		virtual std::unique_ptr<IChunkBIterator> copy() const = 0;
		virtual bool equal(const IChunkBIterator *other) const = 0;
		virtual void move(int64_t shift) = 0;
		virtual const CubA4::world::BlockInChunkPos &get() const = 0;
	protected:
		explicit IChunkBIterator() = default;
	};
}
