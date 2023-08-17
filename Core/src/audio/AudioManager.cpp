#include <audio/AudioManager.hpp>
#include <audio/IAudioPlayer.hpp>
using namespace CubA4::audio;


AudioManager::AudioManager(std::shared_ptr<IAudioPlayer> player) :
	player_(player), importer_(player->getBufferPool()), trackManager_(player_->getSourcePool())
{

}

IAudioImporter &AudioManager::getImporter()
{
	return importer_;
}

IAudioListener &AudioManager::getListener()
{
	return player_->getListener();
}

IAudioTrackManager &AudioManager::getTrackManager()
{
	return trackManager_;
}