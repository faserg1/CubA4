#ifndef RENDERBASE_IWORLDMANAGER_HPP
#define RENDERBASE_IWORLDMANAGER_HPP

#include <cstdint>
#include <world/IChunk.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace world
			{
				class IWorldManager
				{
				public:
					virtual void setCameraPosition(CubA4::mod::world::ChunkPos globalPos, float x, float y, float z) = 0;
					/**
					\param roll Вращение вокруг оси x
					\param pitch Вращение вокруг оси y
					\param yaw Вращение вокруг оси z
					**/
					virtual void setCameraRotation(float roll, float pitch, float yaw) = 0;
					virtual void setFieldOfView(float degrees) = 0;
				protected:
					explicit IWorldManager() = default;
					virtual ~IWorldManager() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_IWORLDMANAGER_HPP
