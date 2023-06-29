#pragma once

#include <memory>
#include <world/WorldGeneratorStep.hpp>

namespace CubA4::world
{
	class IWorld;

	class IWorldGeneratorData
	{
	public:
		
	protected:
		explicit IWorldGeneratorData() = default;
		virtual ~IWorldGeneratorData() = default;
	private:
		// step (stage)
		// seed
		// maps? 
	};
}


