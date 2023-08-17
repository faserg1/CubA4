#pragma once

#include <memory>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class IAudioBuffer;

	class IAudioSource
	{
	public:
		virtual ~IAudioSource() = default;

		virtual void attachBuffer(std::shared_ptr<IAudioBuffer> buffer) = 0;
		virtual void play() = 0;
		virtual void stop() = 0;

		virtual void setPosition(const CubA4::world::GlobalPosition &pos) = 0;
	protected:
		IAudioSource() = default;
		
	};
}
