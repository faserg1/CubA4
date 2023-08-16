#include <audio/AudioPlayer.hpp>
#include <audio/IAudioTrack.hpp>
#include <stdexcept>
#include <AL/al.h>
#include <AL/alc.h>
using namespace CubA4::audio;

struct AudioPlayer::Data
{
	ALCdevice *device = nullptr;
	ALCcontext *context = nullptr;
};

AudioPlayer::AudioPlayer() : 
	data_(std::make_unique<Data>())
{
	auto error = alGetError();
	data_->device = alcOpenDevice(nullptr);
	if (!data_->device)
		throw std::runtime_error("Cannot open audio device");
	error = alGetError();
	

	data_->context = alcCreateContext(data_->device, nullptr);
	error = alGetError();

	alcMakeContextCurrent(data_->context);
	error = alGetError();

	ALfloat listenerPos[]={1.0,1.0,1.0};
	ALfloat listenerVel[]={0.0,0.0,0.0};
	ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};

	alListenerfv(AL_POSITION,listenerPos);
	alListenerfv(AL_VELOCITY,listenerVel);
	alListenerfv(AL_ORIENTATION,listenerOri);
	error = alGetError();
}

AudioPlayer::~AudioPlayer()
{
	alcDestroyContext(data_->context);
	alcCloseDevice(data_->device);
}

void AudioPlayer::play(std::shared_ptr<const IAudioTrack> track, const CubA4::world::GlobalPosition &pos)
{
	// TODO: return handle (to destroy buffers)
	ALuint bufferId = 0;
	alGenBuffers(1, &bufferId);
	auto error = alGetError();
	auto &samples = track->getSamples();
	const auto bufferSize = static_cast<ALsizei>(samples.size() * sizeof(int16_t));
	alBufferData(bufferId, AL_FORMAT_STEREO16, samples.data(), bufferSize, track->getRate());
	error = alGetError();

	ALuint sourceId = 0;
	alGenSources(1, &sourceId);
	error = alGetError();
	alSourcei(sourceId, AL_BUFFER, bufferId);
	error = alGetError();

	auto floatPos = pos.globalPos<float>();

	alSource3f(sourceId, AL_POSITION, floatPos.x, floatPos.y, floatPos.z);

	alSourcef(sourceId, AL_PITCH, 1.0f);
	alSourcef(sourceId, AL_GAIN, .5f);

	alSourcePlay(sourceId);
	error = alGetError();
}

void AudioPlayer::setListenerPosition(const CubA4::world::GlobalPosition &pos)
{
	auto floatPos = pos.globalPos<float>();
	alListener3f(AL_POSITION, floatPos.x, floatPos.y, floatPos.z);
}
