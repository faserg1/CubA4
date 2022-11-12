#pragma once

#include <memory>
#include <array>
#include <cstdint>

#include <world/Position.hpp>
#include <world/Sides.hpp>
#include <object/IBlock.hpp>

namespace CubA4::world
{
	constexpr const uint8_t BoundsSize = 2;
	
	/// Диапазон блоков в чанке
	class IChunkRange
	{
	public:
		class Iterator;
		using Bounds = std::array<world::BlockInChunkPos, BoundsSize>;
	public:
		/// Возвращает блок, который заполняет этот диапазон
		virtual std::shared_ptr<const object::IBlock> getBlock() const = 0;
		/* \brief Получает границы диапазона блоков в чанке
			* \return Возвращает координаты диапазона чанка
			* \see BoundsSize
		*/
		virtual const Bounds &getBounds() const = 0;
		virtual Bounds getSideRect(BlockSide side) const = 0;
		/// Возвращает количество заполняемых блоков в диапазоне
		virtual uint32_t getBlockCount() const = 0;
		virtual uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const = 0; 
		/// Получает слой, на котором расположены блоки
		virtual CubA4::world::Layer getLayer() const = 0;
		virtual Iterator begin() const = 0;
		virtual Iterator end() const = 0;
	protected:
		explicit IChunkRange() = default;
		virtual ~IChunkRange() = default;
	};

	class IChunkRange::Iterator
	{
		
	public:
		using value_type = world::BlockInChunkPos;
		using difference_type = std::ptrdiff_t;
		using reference = const world::BlockInChunkPos&;
		using pointer = const world::BlockInChunkPos*;
		using iterator_category = std::forward_iterator_tag;
		explicit Iterator() : range_(nullptr) {}
		explicit Iterator(const IChunkRange *range, world::BlockInChunkPos pos, uint32_t index) : range_(range), current_(pos), index_(index) {}
		Iterator(const Iterator &other) = default;
		bool operator==(const Iterator &other) const
		{
			return range_ == other.range_ && index_ == other.index_;
		}
		bool operator!=(const Iterator &other) const = default;
		Iterator &operator--()
		{
			return back();
		}
		Iterator &operator++()
		{
			return forward();
		}
		Iterator operator--(int)
		{
			auto it = *this;
			back();
			return it;
		}
		Iterator operator++(int)
		{
			auto it = *this;
			forward();
			return it;
		}
		const CubA4::world::BlockInChunkPos &operator*() const
		{
			return current_;
		}
		const CubA4::world::BlockInChunkPos *operator->() const
		{
			return &current_;
		}
	private:
		Iterator &back()
		{
			if (index_ == 0)
			{
				// Assert?
				return *this;
			}
			auto func = [this](decltype(current_.x) decltype(current_)::*coord) -> bool
			{
				if (current_.*coord > range_->getBounds()[0].*coord)
				{
					(current_.*coord)--;
					return false;
				}
				(current_.*coord) = range_->getBounds()[1].*coord;
				return true;
			};
			index_--;
			func(&decltype(current_)::x) && func(&decltype(current_)::y) && func(&decltype(current_)::z);
			return *this;
		}
		Iterator &forward()
		{
			if (index_ > range_->getBlockCount())
			{
				// Assert?
				return *this;
			}
			auto func = [this](decltype(current_.x) decltype(current_)::*coord) -> bool
			{
				if (current_.*coord < range_->getBounds()[1].*coord)
				{
					(current_.*coord)++;
					return false;
				}
				(current_.*coord) = range_->getBounds()[0].*coord;
				return true;
			};
			index_++;
			func(&decltype(current_)::x) && func(&decltype(current_)::y) && func(&decltype(current_)::z);
			return *this;
		}
	private:
		const IChunkRange *range_;
		CubA4::world::BlockInChunkPos current_;
		uint32_t index_;
	};
}
