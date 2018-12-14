#ifndef RENDERBASE_IWORLDMANAGER_HPP
#define RENDERBASE_IWORLDMANAGER_HPP

#include <cstdint>

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
					virtual void setCameraPosition(double x, double y, double z) = 0;
					/**
					\param roll Вращение вокруг оси x
					\param pitch Вращение вокруг оси y
					\param yaw Вращение вокруг оси z
					**/
					virtual void setCameraRotation(double roll, double pitch, double yaw) = 0;
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
