#ifndef IWORLDGENERATOR_HPP
#define IWORLDGENERATOR_HPP

#include <memory>
#include "IChunk.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorld;

			class IWorldGenerator
			{
			public:
				virtual void generateChunk(std::shared_ptr<IWorld> world, const ChunkPos &chunkPos) = 0;
			protected:
				explicit IWorldGenerator() = default;
				virtual ~IWorldGenerator() = default;
			private:
			};
		}
	}
}

#endif // IWORLDGENERATOR_HPP
