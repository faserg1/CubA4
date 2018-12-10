#ifndef RENDERVULKAN_IRENDERENGINEPIPELINEUPDATER_HPP
#define RENDERVULKAN_IRENDERENGINEPIPELINEUPDATER_HPP

#include <vector>
#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IChunk;
		}
	}

	namespace render
	{
		namespace engine
		{
			namespace pipeline
			{
				class IRenderEnginePipelineUpdater
				{
				public:
					virtual void pushChunks(std::vector<std::shared_ptr<const CubA4::mod::world::IChunk>> chunks) = 0;
				protected:
					explicit IRenderEnginePipelineUpdater() = default;
					virtual ~IRenderEnginePipelineUpdater() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_IRENDERENGINEPIPELINEUPDATER_HPP
