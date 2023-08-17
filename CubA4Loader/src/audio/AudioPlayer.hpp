#pragma once

#include <memory>
#include <audio/IAudioPlayer.hpp>

namespace CubA4::audio
{
	class AudioPlayer : public virtual IAudioPlayer
	{
		struct Data;
	public:
		AudioPlayer();
		~AudioPlayer();

		IAudioListener &getListener() override;
		IAudioBufferPool &getBufferPool() override;
		IAudioSourcePool &getSourcePool() override;
	private:
		std::unique_ptr<Data> data_;
	};
}