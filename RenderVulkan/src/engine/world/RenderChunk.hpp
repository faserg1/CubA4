#pragma once

#include <world/IChunk.hpp>
#include <engine/pipeline/RenderFramebufferData.hpp>
#include <engine/model/RenderModel.hpp>
#include <engine/material/Material.hpp>
#include <vector>
#include <map>
#include <vulkan/vulkan.h>
#include <functional>

namespace CubA4::render::engine::world
{
	class RenderChunk
	{
	public:
		struct Data
		{
			using MaterialPtr = std::shared_ptr<const CubA4::render::engine::material::Material>;
			using RenderModels = std::map<MaterialPtr, std::shared_ptr<const CubA4::render::engine::model::RenderModel>>;
			CubA4::world::ChunkPos pos;
			std::vector<VkCommandBuffer> cmdBuffers;
			RenderModels compiledBlockData;
			CubA4::render::engine::pipeline::RenderFramebufferData data;
		};
		explicit RenderChunk(Data data, std::function<void()> deleter);
		~RenderChunk();

		void executeFrom(VkCommandBuffer primaryCmdBuffer) const;
		const CubA4::world::ChunkPos &getChunkPos() const;
		const Data::RenderModels &getBlockData() const;
		const CubA4::render::engine::pipeline::RenderFramebufferData &getPipelineData() const;
	protected:
	private:
		const Data data_;
		const std::function<void()> deleter_;
	};
}
