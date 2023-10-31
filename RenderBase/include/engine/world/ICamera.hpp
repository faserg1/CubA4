#pragma once

#include <world/GlobalPosition.hpp>
#include <engine/world/Ray.hpp>

namespace CubA4::render::engine::world
{
	class ICamera
	{
	public:
		virtual ~ICamera() = default;

		virtual CubA4::world::GlobalPosition getPosition() const = 0;
		virtual void setPosition(CubA4::world::GlobalPosition position) = 0;
		virtual void setRotation(float roll, float pitch, float yaw) = 0;
		virtual void move(float x, float y, float z, bool local = true) = 0;
		virtual void rotate(float roll, float pitch, float yaw) = 0;

		virtual Ray getRay(uint64_t x, uint64_t y) const = 0;
		virtual Ray getRay() const = 0;
	protected:
		explicit ICamera() = default;
	};
}
