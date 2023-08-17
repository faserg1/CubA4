#include <audio/AudioPlayer.hpp>
#include <audio/IAudioTrack.hpp>
#include <audio/AudioBufferPool.hpp>
#include <audio/AudioSourcePool.hpp>
#include <audio/AudioListener.hpp>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>
using namespace CubA4::audio;

struct AudioPlayer::Data
{
	ALCdevice *device = nullptr;
	ALCcontext *context = nullptr;

	std::shared_ptr<AudioBufferPool> bufferPool;
	std::shared_ptr<AudioSourcePool> sourcePool;
	AudioListener listener;
};

AudioPlayer::AudioPlayer() : 
	data_(std::make_unique<Data>())
{
	data_->device = alcOpenDevice(nullptr);
	if (!data_->device)
		throw std::runtime_error("Cannot open audio device");
	data_->context = alcCreateContext(data_->device, nullptr);
	alcMakeContextCurrent(data_->context);

	data_->bufferPool = std::make_shared<AudioBufferPool>();
	data_->sourcePool = std::make_shared<AudioSourcePool>();
	data_->listener.init();
}

AudioPlayer::~AudioPlayer()
{
	alcDestroyContext(data_->context);
	alcCloseDevice(data_->device);
}

IAudioListener &AudioPlayer::getListener()
{
	return data_->listener;
}

IAudioBufferPool &AudioPlayer::getBufferPool()
{
	return *data_->bufferPool;
}

IAudioSourcePool &AudioPlayer::getSourcePool()
{
	return *data_->sourcePool;
}
