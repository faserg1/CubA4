#pragma once

#include <world/IChunk.hpp>
#include <engine/model/IRenderModel.hpp>
#include <vector>
#include <vulkan/vulkan.h>
#include <functional>

namespace CubA4::render::engine::world
{
	class RenderChunk
	{
	public:
		struct Data
		{
			CubA4::world::ChunkPos pos;
			std::vector<VkCommandBuffer> cmdBuffers;
			std::vector<std::shared_ptr<const CubA4::render::engine::model::IRenderModel>> compiledBlockData;
		};
		explicit RenderChunk(Data data, std::function<void()> deleter);
		~RenderChunk();

		void executeFrom(VkCommandBuffer primaryCmdBuffer) const;
		const CubA4::world::ChunkPos &getChunkPos() const;
	protected:
	private:
		const Data data_;
		const std::function<void()> deleter_;
	};
}
