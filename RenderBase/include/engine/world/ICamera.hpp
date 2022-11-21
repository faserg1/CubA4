#pragma once

#include <world/Position.hpp>

namespace CubA4::render::engine::world
{
	class ICamera
	{
	public:
		virtual ~ICamera() = default;

		virtual void setPosition(float x, float y, float z, CubA4::world::ChunkPos chunkPos) = 0;
		virtual void setRotation(float roll, float pitch, float yaw) = 0;
		virtual void move(float x, float y, float z, bool local = true) = 0;
		virtual void rotate(float roll, float pitch, float yaw) = 0;
	protected:
		explicit ICamera() = default;
	};
}
