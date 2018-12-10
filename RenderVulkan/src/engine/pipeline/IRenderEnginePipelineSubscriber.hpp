#ifndef RENDERVULKAN_IRENDERENGINEPIPELINESUBSCRIBER_HPP
#define RENDERVULKAN_IRENDERENGINEPIPELINESUBSCRIBER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace world
			{
				class RenderChunk;
			}

			namespace pipeline
			{
				class IRenderEnginePipelineSubscriber
				{
				public:
					virtual void chunkCompiled(std::shared_ptr<const CubA4::render::engine::world::RenderChunk> renderChunk) = 0;
				protected:
					explicit IRenderEnginePipelineSubscriber() = default;
					virtual ~IRenderEnginePipelineSubscriber() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_IRENDERENGINEPIPELINESUBSCRIBER_HPP
