#pragma once

#include <memory>
#include <audio/IAudioBuffer.hpp>
#include <resources/IResource.hpp>

namespace CubA4::audio
{
	class IAudioImporter
	{
	public:
		virtual std::shared_ptr<IAudioBuffer> importTrack(std::shared_ptr<const CubA4::resources::IResource> resource) = 0;
	protected:
		IAudioImporter() = default;
	};
}