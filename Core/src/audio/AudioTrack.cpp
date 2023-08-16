#include <audio/AudioTrack.hpp>
using namespace CubA4::audio;

AudioTrack::AudioTrack(std::vector<int16_t> samples, uint32_t rate) :
	samples_(samples), rate_(rate)
{

}

const std::vector<int16_t> &AudioTrack::getSamples() const
{
	return samples_;
}

uint32_t AudioTrack::getRate() const
{
	return rate_;
}