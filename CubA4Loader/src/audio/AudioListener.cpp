#include <audio/AudioListener.hpp>
#include <al/al.h>
using namespace CubA4::audio;

AudioListener::AudioListener()
{

}

AudioListener::~AudioListener()
{

}

void AudioListener::init()
{
	ALfloat listenerPos[]={1.0,1.0,1.0};
	ALfloat listenerVel[]={0.0,0.0,0.0};
	ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};

	alListenerfv(AL_POSITION,listenerPos);
	alListenerfv(AL_VELOCITY,listenerVel);
	alListenerfv(AL_ORIENTATION,listenerOri);
}

void AudioListener::setPosition(const CubA4::world::GlobalPosition &pos)
{
	auto floatPos = pos.globalPos<float>();
	alListener3f(AL_POSITION, floatPos.x, floatPos.y, floatPos.z);
}

void AudioListener::setVelocity(const CubA4::Vector3 &velocity)
{
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}