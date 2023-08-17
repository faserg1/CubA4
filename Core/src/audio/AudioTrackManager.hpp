#pragma once

#include <memory>
#include <audio/IAudioTrackManager.hpp>

namespace CubA4::audio
{
	class IAudioSourcePool;

	class AudioTrackManager :
		public virtual IAudioTrackManager
	{
	public:
		AudioTrackManager(IAudioSourcePool &sourcePool);

		std::shared_ptr<IAudioTrack> createTrack() override;
	private:
		IAudioSourcePool &sourcePool_;
	};
}