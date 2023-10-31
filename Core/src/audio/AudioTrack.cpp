#include <audio/AudioTrack.hpp>
#include <audio/IAudioSource.hpp>
using namespace CubA4::audio;

AudioTrack::AudioTrack(std::unique_ptr<IAudioSource> source) :
	source_(std::move(source))
{

}

AudioTrack::~AudioTrack() = default;

void AudioTrack::attachBuffer(std::shared_ptr<IAudioBuffer> buffer)
{
	source_->attachBuffer(buffer);
}

void AudioTrack::play()
{
	source_->play();
}

void AudioTrack::stop()
{
	source_->stop();
}

void AudioTrack::setVolume(float volume)
{
	source_->setVolume(volume);
}

void AudioTrack::setPosition(const CubA4::world::GlobalPosition &pos)
{
	source_->setPosition(pos);
}

void AudioTrack::setVelocity(const CubA4::Vector3 &velocity)
{
	source_->setVelocity(velocity);
}