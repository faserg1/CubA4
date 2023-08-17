#include <audio/AudioTrackManager.hpp>
#include <audio/AudioTrack.hpp>
#include <audio/IAudioSourcePool.hpp>
#include <audio/IAudioSource.hpp>
using namespace CubA4::audio;

AudioTrackManager::AudioTrackManager(IAudioSourcePool &sourcePool) :
	sourcePool_(sourcePool)
{

}

std::shared_ptr<IAudioTrack> AudioTrackManager::createTrack()
{
	return std::make_shared<AudioTrack>(sourcePool_.getSource());
}