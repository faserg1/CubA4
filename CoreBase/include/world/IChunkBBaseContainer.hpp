#pragma once

#include <memory>
#include <world/Position.hpp>
#include <world/BlockData.hpp>
#include <object/IBlock.hpp>
#include <world/IChunkBIterator.hpp>

namespace CubA4::world
{
	enum class ChunkBContainerType
	{
		Range,
		Set,
		Multi
	};

	/** @brief Basic chunk block container
	 * 
	*/
	class IChunkBBaseContainer
	{
	public:
		class Iterator;
	public:
		virtual ~IChunkBBaseContainer() = default;

		virtual ChunkBContainerType getType() const = 0;
		/// Возвращает блок, который заполняет этот диапазон
		virtual std::shared_ptr<const object::IBlock> getBlock() const = 0;
		/// Возвращает количество заполняемых блоков в диапазоне
		virtual uint32_t getBlockCount() const = 0;
		/// Получает слой, на котором расположены блоки
		virtual CubA4::world::Layer getLayer() const = 0;
		virtual uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const = 0;
		virtual const BlockData &getBlockData(const world::BlockInChunkPos &pos) const = 0;

		virtual Iterator begin() const = 0;
		virtual Iterator end() const = 0;
	protected:
		explicit IChunkBBaseContainer() = default;
	};

	class IChunkBBaseContainer::Iterator
	{
	public:
		using value_type = world::BlockInChunkPos;
		using difference_type = std::ptrdiff_t;
		using reference = const world::BlockInChunkPos&;
		using pointer = const world::BlockInChunkPos*;
		using iterator_category = std::random_access_iterator_tag;

		explicit Iterator() {}
		explicit Iterator(std::unique_ptr<IChunkBIterator> impl) : impl_(std::move(impl)) {}
		Iterator(const Iterator &other) : impl_(other.impl_->copy()) {}
		bool operator==(const Iterator &other) const
		{
			return (impl_ && impl_->equal(other.impl_.get())) || (!impl_ && !other.impl_);
		}
		bool operator!=(const Iterator &other) const = default;
		Iterator &operator--()
		{
			impl_->move(-1);
			return *this;
		}
		Iterator &operator++()
		{
			impl_->move(1);
			return *this;
		}
		Iterator operator--(int)
		{
			auto it = *this;
			impl_->move(-1);
			return it;
		}
		Iterator operator++(int)
		{
			auto it = *this;
			impl_->move(1);
			return it;
		}
		const CubA4::world::BlockInChunkPos &operator*() const
		{
			return impl_->get();
		}
		const CubA4::world::BlockInChunkPos *operator->() const
		{
			return &impl_->get();
		}
	private:
		std::unique_ptr<IChunkBIterator> impl_;
	};
}
