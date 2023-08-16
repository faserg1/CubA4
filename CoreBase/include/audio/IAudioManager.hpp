#pragma once

#include <memory>
#include <audio/IAudioTrack.hpp>
#include <resources/IResource.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class IAudioManager
	{
	public:
		virtual std::shared_ptr<IAudioTrack> createTrack(std::shared_ptr<const CubA4::resources::IResource> resource) = 0;
		virtual void play(std::shared_ptr<IAudioTrack> track, const CubA4::world::GlobalPosition &pos) = 0;
	protected:
		IAudioManager() = default;
	};
}