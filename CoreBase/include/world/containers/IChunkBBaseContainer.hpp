#pragma once

#include <memory>
#include <world/Position.hpp>
#include <world/data/BlockData.hpp>
#include <object/IBlock.hpp>
#include <world/containers/IChunkBIterator.hpp>

namespace CubA4::world
{
	/** @brief Basic chunk block container
	 * 
	*/
	class IChunkBBaseContainer
	{
	public:
		class Iterator;
	public:
		virtual ~IChunkBBaseContainer() = default;

		/// Возвращает идентификатор контейнера (уникален для чанка)
		virtual size_t getId() const = 0;
		/// Is container index are global (if local, index should not be used as global position index)
		virtual bool isIndexGlobal() const = 0;
		/// Возвращает блок, который заполняет этот диапазон
		virtual std::shared_ptr<const object::IBlock> getBlock() const = 0;
		/// Возвращает количество заполняемых блоков в диапазоне
		virtual uint32_t getBlockCount() const = 0;
		/// Получает слой, на котором расположены блоки
		virtual CubA4::world::Layer getLayer() const = 0;
		virtual bool hasBlockAt(const world::BlockInChunkPos &pos) const = 0;
		virtual bool hasBlockAt(uint32_t index) const = 0;
		virtual uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const = 0;
		virtual uint32_t getBlockLocalIndex(const world::BlockInChunkPos &pos) const = 0;
		virtual CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const = 0;
		virtual CubA4::world::BlockInChunkPos getBlockPositionLocal(uint32_t localIndex) const = 0;
		virtual decltype(BlockData::id) getBlockData(const world::BlockInChunkPos &pos) const = 0;
		virtual decltype(BlockData::id) getBlockData(uint32_t index) const = 0;

		virtual Iterator begin() const = 0;
		virtual Iterator end() const = 0;
	protected:
		explicit IChunkBBaseContainer() = default;
	};

	class IChunkBBaseContainer::Iterator
	{
	public:
		using value_type = world::BlockInChunkPos;
		using difference_type = int32_t;
		using reference = const world::BlockInChunkPos&;
		using pointer = const world::BlockInChunkPos*;
		using iterator_category = std::forward_iterator_tag;
		//using iterator_category = std::random_access_iterator_tag;

		Iterator() {}
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
		Iterator operator+(const difference_type offset) const
		{
			auto it = *this;
			impl_->move(offset);
			return it;
		}
		Iterator operator-(const difference_type offset) const
		{
			auto it = *this;
			impl_->move(-offset);
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
		Iterator &operator=(const Iterator& other)
		{
			impl_.reset();
			impl_ = std::move(other.impl_->copy());
			return *this;
		}
	private:
		std::unique_ptr<IChunkBIterator> impl_;
	};
}
