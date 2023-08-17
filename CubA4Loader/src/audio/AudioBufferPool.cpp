#include <audio/AudioBufferPool.hpp>
#include <audio/AudioBuffer.hpp>
#include <al/al.h>
#include <array>
using namespace CubA4::audio;

AudioBufferPool::AudioBufferPool()
{

}

AudioBufferPool::~AudioBufferPool()
{

}

std::shared_ptr<IAudioBuffer> AudioBufferPool::getBuffer()
{
	if (bufferIds_.empty())
		allocateBuffers();
	auto id = bufferIds_.back();
	bufferIds_.pop_back();
	std::shared_ptr<IAudioPool> pool = shared_from_this();
	return std::make_shared<AudioBuffer>(id, pool);
}

void AudioBufferPool::free(IdType id)
{
	bufferIds_.push_back(id);
}

void AudioBufferPool::allocateBuffers()
{
	std::array<uint32_t, allocationCount_> buffers;
	alGenBuffers(allocationCount_, buffers.data());
	bufferIds_.append_range(buffers);
}

void AudioBufferPool::deallocateBuffers()
{

}