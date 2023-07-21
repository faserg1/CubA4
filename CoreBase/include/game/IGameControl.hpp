#pragma once

#include <memory>
#include <string>
#include <world/IWorldControl.hpp>

namespace CubA4::game
{
	class IGameControl
	{
	public:
		virtual ~IGameControl() = default;
		virtual bool requestWorldChange(const std::string &worldId, const std::string &dimId) = 0;
		virtual CubA4::world::IWorldControl &getWorldControl() = 0;
	protected:
		IGameControl() = default;
	};
}