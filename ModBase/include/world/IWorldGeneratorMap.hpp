#pragma once

#include <memory>
#include <world/WorldGeneratorStep.hpp>

namespace CubA4::world
{
	class IWorld;

	class IWorldGeneratorMap
	{
	public:
		virtual int16_t getScale() const = 0;
	protected:
		explicit IWorldGeneratorMap() = default;
		virtual ~IWorldGeneratorMap() = default;
	private:
		// scale
	};
}


