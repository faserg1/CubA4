#include <audio/AudioSourcePool.hpp>
#include <audio/AudioSource.hpp>
#include <al/al.h>
#include <array>
using namespace CubA4::audio;

AudioSourcePool::AudioSourcePool()
{

}

AudioSourcePool::~AudioSourcePool()
{

}

std::unique_ptr<IAudioSource> AudioSourcePool::getSource()
{
	if (sourceIds_.empty())
		allocateSources();
	auto id = sourceIds_.back();
	sourceIds_.pop_back();
	std::shared_ptr<IAudioPool> pool = shared_from_this();
	return std::make_unique<AudioSource>(id, pool);
}

void AudioSourcePool::free(IdType id)
{
	sourceIds_.push_back(id);
}

void AudioSourcePool::allocateSources()
{
	std::array<uint32_t, allocationCount_> buffers;
	alGenSources(allocationCount_, buffers.data());
	sourceIds_.append_range(buffers);
}

void AudioSourcePool::deallocateSources()
{

}