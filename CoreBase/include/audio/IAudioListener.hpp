#pragma once

#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class IAudioListener
	{
	public:
		virtual void setPosition(const CubA4::world::GlobalPosition &pos) = 0;
	protected:
		IAudioListener() = default;
		virtual ~IAudioListener() = default;
	};
}