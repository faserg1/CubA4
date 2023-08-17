#pragma once

#include <audio/IAudioImporter.hpp>

namespace CubA4::audio
{
	class IAudioBufferPool;

	class AudioImporter :
		public virtual IAudioImporter
	{
	public:
		AudioImporter(IAudioBufferPool &bufferPool);

		std::shared_ptr<IAudioBuffer> importTrack(std::shared_ptr<const CubA4::resources::IResource> resource) override;
	private:
		std::shared_ptr<IAudioBuffer> createFromOgg(std::shared_ptr<const CubA4::resources::IResource> resource);
	private:
		IAudioBufferPool &bufferPool_;
	};
}