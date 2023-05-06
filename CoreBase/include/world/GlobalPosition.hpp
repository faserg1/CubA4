#pragma once

#include <world/Position.hpp>
#include <cmath>
#include <tuple>

namespace CubA4::world
{
	class GlobalPosition final
	{
	public:
		GlobalPosition() = default;
		explicit GlobalPosition(BasePos<long double> globalPos)
		{
			clampGlobal(globalPos);
		}
		explicit GlobalPosition(ChunkPos chunkPos, BlockInChunkPos blockPos, BasePos<float> inBlockPos) :
			chunkPos_(chunkPos), blockPosition_(blockPos), inBlockPos_(inBlockPos)
		{
			clampPos();
		}
		GlobalPosition &operator+=(GlobalPosition &other)
		{
			chunkPos_ += other.chunkPos_;
			blockPosition_ += other.blockPosition_;
			inBlockPos_ += other.inBlockPos_;
			clampPos();
			return *this;
		}
		GlobalPosition &operator-=(GlobalPosition &other)
		{
			chunkPos_ -= other.chunkPos_;
			blockPosition_ -= other.blockPosition_;
			inBlockPos_ -= other.inBlockPos_;
			clampPos();
			return *this;
		}
		GlobalPosition &operator+=(const ChunkPos &pos)
		{
			chunkPos_ += pos;
			clampPos();
			return *this;
		}
		GlobalPosition &operator-=(const ChunkPos &pos)
		{
			chunkPos_ -= pos;
			clampPos();
			return *this;
		}
		GlobalPosition &operator+=(const BlockInChunkPos &pos)
		{
			blockPosition_ += pos;
			clampPos();
			return *this;
		}
		GlobalPosition &operator-=(const BlockInChunkPos &pos)
		{
			blockPosition_ -= pos;
			clampPos();
			return *this;
		}
		GlobalPosition &operator+=(const BasePos<float> &pos)
		{
			inBlockPos_ += pos;
			clampPos();
			return *this;
		}
		GlobalPosition &operator-=(const BasePos<float> &pos)
		{
			inBlockPos_ -= pos;
			clampPos();
			return *this;
		}
		const ChunkPos &chunkPos() const
		{
			return chunkPos_;
		}
		const BlockInChunkPos &blockPosition() const
		{
			return blockPosition_;
		}
		const BasePos<float> &inBlockPos() const
		{
			return inBlockPos_;
		}
		std::tuple<ChunkPos, BlockInChunkPos, BasePos<float>> position() const
		{
			return std::make_tuple(chunkPos_, blockPosition_, inBlockPos_);
		}
	protected:
		template <class CoodTypeInside, CoodTypeInside Min, CoodTypeInside Max, class CoordTypeOutside>
		constexpr void clampWith(CoodTypeInside &coord, CoordTypeOutside &outside)
		{
			constexpr const auto Length = Max - Min;
			if (coord >= Max)
			{
				const auto count = std::trunc(std::log(Length)/std::log(coord - Min));
				if (std::isnan(count))
					return;
				coord -= static_cast<CoodTypeInside>(count * Length);
				outside += static_cast<CoordTypeOutside>(count);
			}
			else if (coord <= Min)
			{
				const auto count = std::trunc(std::log(Length)/std::log(coord + Min));
				if (std::isnan(count))
					return;
				coord += static_cast<CoodTypeInside>(count * Length);
				outside -= static_cast<CoordTypeOutside>(count);
			}
		}
		template <class CoodTypeInside, CoodTypeInside Min, CoodTypeInside Max, class CoordTypeOutside>
		constexpr void clampWith(BasePos<CoodTypeInside> &coords, BasePos<CoordTypeOutside> &outside)
		{
			clampWith<CoodTypeInside, Min, Max, CoordTypeOutside>(coords.x, outside.x);
			clampWith<CoodTypeInside, Min, Max, CoordTypeOutside>(coords.y, outside.y);
			clampWith<CoodTypeInside, Min, Max, CoordTypeOutside>(coords.z, outside.z);
		}
		void clampGlobal(BasePos<long double> globalPos)
		{
			clampWith<long double, 0.l, 1.l>(globalPos, blockPosition_);
			inBlockPos_ = convertPos<float>(globalPos);
			clampWith<decltype(BlockInChunkPos::x), 0, ChunkSize>(blockPosition_, chunkPos_);
		}
		void clampPos()
		{
			clampWith<float, 0.f, 1.f>(inBlockPos_, blockPosition_);
			clampWith<decltype(BlockInChunkPos::x), 0, ChunkSize>(blockPosition_, chunkPos_);
		}
	private:
		ChunkPos chunkPos_ = {};
		BlockInChunkPos blockPosition_ = {};
		BasePos<float> inBlockPos_ = {};
	};
}
