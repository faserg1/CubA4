#pragma once

#include <memory>
#include <world/GlobalPosition.hpp>
#include <base/Vector.hpp>

namespace CubA4::audio
{
	class IAudioBuffer;

	class IAudioTrack
	{
	public:
		virtual ~IAudioTrack() = default;

		virtual void attachBuffer(std::shared_ptr<IAudioBuffer> buffer) = 0;
		virtual void play() = 0;
		virtual void stop() = 0;

		virtual void setPosition(const CubA4::world::GlobalPosition &pos) = 0;
		virtual void setVelocity(const CubA4::Vector3 &velocity) = 0;
	protected:
		IAudioTrack() = default;
	};
}
