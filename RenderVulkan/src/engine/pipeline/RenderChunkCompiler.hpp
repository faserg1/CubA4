#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <future>
#include <cstddef>
#include <tuple>
#include <engine/pipeline/RenderChunkCompilerCore.hpp>
#include <engine/pipeline/RenderChunkPipelineData.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class RenderPass;
		}

		namespace engine
		{
			class ResourceManager;
			class RenderManager;
			
			namespace memory
			{
				class IMemoryPart;
			}
			

			namespace world
			{
				class IWorldManager;
				class WorldManager;
				class RenderChunk;
			}

			namespace pipeline
			{
				class RenderChunkCompiler :
					public RenderChunkCompilerCore
				{
				public:
					explicit RenderChunkCompiler(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::RenderPass> renderPass,
						 std::shared_ptr<RenderManager> renderManager);
					explicit RenderChunkCompiler(const RenderChunkCompiler &) = delete;
					~RenderChunkCompiler();

					std::shared_ptr<const world::RenderChunk> compileChunk(std::shared_ptr<const CubA4::world::IChunk> chunk, const RenderChunkPipelineData &data);
					std::shared_ptr<const world::RenderChunk> compileChunk(std::shared_ptr<const world::RenderChunk> chunk, const RenderChunkPipelineData &data);
				protected:
				private:
					const std::shared_ptr<const vulkan::RenderPass> renderPass_;
					const std::shared_ptr<ResourceManager> resourceManager_;
					const std::shared_ptr<const world::WorldManager> worldManager_;
				private:
					std::shared_ptr<const world::RenderChunk> compileChunkInternal(const RenderModels &compiledBlockData, const CubA4::world::ChunkPos &chunkPos, const RenderChunkPipelineData &data);
				};
			}
		}
	}
}
