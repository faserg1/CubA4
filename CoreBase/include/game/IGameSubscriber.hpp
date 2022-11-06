#pragma once

#include <memory>
#include <world/IWorld.hpp>

namespace CubA4::game
{
	class IGameSubscriber
	{
	public:
		virtual void worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld) = 0;
	protected:
		explicit IGameSubscriber() = default;
		virtual ~IGameSubscriber() = default;
	private:
	};
}

