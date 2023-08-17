#include <audio/AudioSource.hpp>
#include <audio/IAudioPool.hpp>
#include <audio/AudioBuffer.hpp>
#include <al/al.h>
using namespace CubA4::audio;

AudioSource::AudioSource(IdType sourceId, std::shared_ptr<IAudioPool> pool) :
	sourceId_(sourceId), pool_(pool)
{
	alSource3f(sourceId, AL_POSITION, 0, 0, 0);

	alSourcef(sourceId, AL_PITCH, 1.f);
	alSourcef(sourceId, AL_GAIN, 1.f);
}

AudioSource::~AudioSource()
{
	if (auto pool = pool_.lock())
		pool->free(sourceId_);
}

void AudioSource::attachBuffer(std::shared_ptr<IAudioBuffer> buffer)
{
	if (attachedBuffer_)
	{
		auto bufferId = attachedBuffer_->getBufferId();
		//alSourceUnqueueBuffers(sourceId_, 1, &bufferId);
		attachedBuffer_.reset();
	}
	auto newBuffer = std::dynamic_pointer_cast<AudioBuffer>(buffer);
	if (!newBuffer)
		return;
	auto bufferId = newBuffer->getBufferId();
	//alSourceQueueBuffers(sourceId_, 1, &bufferId);
	alSourcei(sourceId_, AL_BUFFER, bufferId);
	attachedBuffer_ = newBuffer;
}

void AudioSource::play()
{
	alSourcePlay(sourceId_);
}

void AudioSource::stop()
{
	alSourceStop(sourceId_);
}

void AudioSource::setPosition(const CubA4::world::GlobalPosition &pos)
{
	auto floatPos = pos.globalPos<float>();
	alSource3f(sourceId_, AL_POSITION, floatPos.x, floatPos.y, floatPos.z);
}

AudioSource::IdType AudioSource::getSourceId() const
{
	return sourceId_;
}