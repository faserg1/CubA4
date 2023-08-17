#pragma once

#include <memory>
#include <vector>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class IAudioTrack;
	class IAudioBufferPool;
	class IAudioSourcePool;
	class IAudioListener;

	class IAudioPlayer
	{
	public:
		virtual IAudioListener &getListener() = 0;
		virtual IAudioBufferPool &getBufferPool() = 0;
		virtual IAudioSourcePool &getSourcePool() = 0;
	protected:
		IAudioPlayer() = default;
		virtual ~IAudioPlayer() = default;
	};
}