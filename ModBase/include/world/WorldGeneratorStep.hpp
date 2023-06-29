#pragma once

#include <util/Enums.hpp>
#include <cstdint>

namespace CubA4::world
{

	enum class WorldGeneratorStep : uint8_t
	{
		GlobalBiome = 0x1, ///< aka Water, Ground
		GlobalMaps = 0x2, ///< aka Temperature, Moisture
		Biomes = 0x4,
		HeightMap = 0x8,
		GlobalStructures = 0x10,
		BlockEvolution = 0x20,
		Structures = 0x40,
		Folliage = 0x80
	};

	CUBA4_ENUM_FLAGS_OPERATORS(WorldGeneratorStep, WorldGeneratorSteps, uint8_t)
}
