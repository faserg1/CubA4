#pragma once

#include <memory>
#include <array>
#include <cstdint>

#include <world/Position.hpp>
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
		/// Возвращает количество заполняемых блоков в диапазоне
		virtual uint32_t getBlockCount() const = 0;
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
		Iterator(const IChunkRange *range, world::BlockInChunkPos pos, bool end = false) : range_(range), current_(pos), isEnd_(end) {}
		bool operator==(const Iterator &other) const = default;
		bool operator!=(const Iterator &other) const = default;
		Iterator &operator--()
		{
			if (current_ == range_->getBounds()[0])
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
			[[maybe_unused]] auto isStart = func(&decltype(current_)::x) && func(&decltype(current_)::y) && func(&decltype(current_)::z);
			return *this;
		}
		Iterator &operator++()
		{
			if (isEnd_)
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
			isEnd_ = func(&decltype(current_)::x) && func(&decltype(current_)::y) && func(&decltype(current_)::z);
			return *this;
		}
		CubA4::world::BlockInChunkPos operator*() const
		{
			return current_;
		}
		CubA4::world::BlockInChunkPos operator->() const
		{
			return current_;
		}
	private:
		const IChunkRange *range_;
		CubA4::world::BlockInChunkPos current_;
		bool isEnd_;
	};
}
