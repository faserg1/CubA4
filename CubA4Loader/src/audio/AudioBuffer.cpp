#include <audio/AudioBuffer.hpp>
#include <al/al.h>
using namespace CubA4::audio;

AudioBuffer::AudioBuffer(IdType buffferId, std::shared_ptr<IAudioPool> pool) :
	buffferId_(buffferId), pool_(pool)
{
}

AudioBuffer::~AudioBuffer()
{
	if (auto pool = pool_.lock())
		pool->free(buffferId_);
}

void AudioBuffer::fillDataStereo(uint8_t *data, size_t samplesCount, uint32_t rate)
{
	alBufferData(buffferId_, AL_FORMAT_STEREO8, data, static_cast<ALsizei>(samplesCount * sizeof(uint8_t)), static_cast<ALsizei>(rate));
}

void AudioBuffer::fillDataStereo(int16_t *data, size_t samplesCount, uint32_t rate)
{
	alBufferData(buffferId_, AL_FORMAT_STEREO16, data, static_cast<ALsizei>(samplesCount * sizeof(int16_t)), static_cast<ALsizei>(rate));
}

void AudioBuffer::fillDataMono(uint8_t *data, size_t samplesCount, uint32_t rate)
{
	alBufferData(buffferId_, AL_FORMAT_MONO8, data, static_cast<ALsizei>(samplesCount * sizeof(uint8_t)), static_cast<ALsizei>(rate));
}

void AudioBuffer::fillDataMono(int16_t *data, size_t samplesCount, uint32_t rate)
{
	alBufferData(buffferId_, AL_FORMAT_MONO16, data, static_cast<ALsizei>(samplesCount * sizeof(int16_t)), static_cast<ALsizei>(rate));
}

AudioBuffer::IdType AudioBuffer::getBufferId() const
{
	return buffferId_;
}