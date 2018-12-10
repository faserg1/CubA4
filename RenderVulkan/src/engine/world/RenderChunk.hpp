#ifndef RENDERVULKAN_RENDERCHUNK_HPP
#define RENDERVULKAN_RENDERCHUNK_HPP

#include <world/IChunk.hpp>
#include <vector>
#include <vulkan/vulkan.h>
#include <functional>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace world
			{
				class RenderChunk
				{
				public:
					explicit RenderChunk(const CubA4::mod::world::ChunkPos &pos, std::vector<VkCommandBuffer> cmdBuffers, std::function<void()> deleter);
					~RenderChunk();

					void executeFrom(VkCommandBuffer primaryCmdBuffer) const;
					const CubA4::mod::world::ChunkPos &getChunkPos() const;
				protected:
				private:
					const CubA4::mod::world::ChunkPos pos_;
					const std::vector<VkCommandBuffer> cmdBuffers_;
					const std::function<void()> deleter_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERCHUNK_HPP
