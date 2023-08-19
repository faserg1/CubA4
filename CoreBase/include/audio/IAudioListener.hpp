#pragma once

#include <world/GlobalPosition.hpp>
#include <base/Vector.hpp>

namespace CubA4::audio
{
	class IAudioListener
	{
	public:
		virtual void setPosition(const CubA4::world::GlobalPosition &pos) = 0;
		virtual void setVelocity(const CubA4::Vector3 &velocity) = 0;
	protected:
		IAudioListener() = default;
		virtual ~IAudioListener() = default;
	};
}