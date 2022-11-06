#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <future>
#include <cstddef>
#include <tuple>
#include "RenderChunkCompilerCore.hpp"

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
		namespace vulkan
		{
			class RenderPass;
		}

		namespace engine
		{
			class ResourceManager;
			
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
					explicit RenderChunkCompiler(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::RenderPass> renderPass,
						 std::shared_ptr<ResourceManager> resourceManager, std::shared_ptr<const world::IWorldManager> worldManager);
					explicit RenderChunkCompiler(const RenderChunkCompiler &) = delete;
					~RenderChunkCompiler();

					std::future<std::shared_ptr<const world::RenderChunk>> compileChunk(std::shared_ptr<const CubA4::world::IChunk> chunk);
				protected:
				private:
					const std::shared_ptr<const vulkan::RenderPass> renderPass_;
					const std::shared_ptr<ResourceManager> resourceManager_;
					const std::shared_ptr<const world::WorldManager> worldManager_;
				private:
					std::shared_ptr<const world::RenderChunk> compileChunkInternal(std::shared_ptr<const CubA4::world::IChunk> chunk);
					std::tuple<VkBuffer, std::shared_ptr<const CubA4::render::engine::memory::IMemoryPart>>
						createBufferFromData(void *data, size_t size, VkBufferUsageFlags flags) const;
					VkDescriptorSet prepareSetWithBuffer(VkDescriptorPool pool, VkDescriptorSetLayout layout, VkBuffer buffer, VkDescriptorType type, uint32_t binding) const;
				};
			}
		}
	}
}
