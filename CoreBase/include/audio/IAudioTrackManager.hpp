#pragma once

#include <memory>
#include <audio/IAudioTrack.hpp>

namespace CubA4::audio
{
	class IAudioTrackManager
	{
	public:
		virtual std::shared_ptr<IAudioTrack> createTrack() = 0;

		virtual ~IAudioTrackManager() = default;
	protected:
		IAudioTrackManager() = default;
	};
}