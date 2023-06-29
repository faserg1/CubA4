#pragma once

#include <memory>
#include <vector>
#include <model/PrimitiveTypes.hpp>
#include <engine/debug/IRenderDebugCollection.hpp>
#include <engine/debug/IRenderDebugInternal.hpp>
#include <engine/memory/IMemoryPart.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/RenderPass.hpp>
#include <vulkan/pipeline/Pipeline.hpp>

namespace CubA4::render::engine::debug
{
	class RenderDebugCollection : public virtual IRenderDebugCollection
	{
		struct DebugModel
		{
			PipelineType type;
			DebugRenderModel renderModel;
			
			CubA4::world::ChunkPos chunkPos;
		};
	public:
		RenderDebugCollection(vulkan::CommandPool &cmdPool, std::shared_ptr<vulkan::RenderPass> renderPass,
			std::shared_ptr<IRenderDebugInternal> internalEvents);
		~RenderDebugCollection();

		void addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to) override;
		void hide() override;
		void show() override;
		bool isVisible() const override;
		void toggleVisibility() override;

		void record(VkCommandBuffer primaryBuffer, uint32_t subpass, VkExtent2D extent);
	protected:
		bool visible_ = true;
	private:
		vulkan::CommandPool &cmdPool_;
		const std::shared_ptr<vulkan::RenderPass> renderPass_;
		const std::weak_ptr<IRenderDebugInternal> internal_;

		std::vector<DebugModel> models_;

		VkCommandBuffer buffer_ = {};
		std::vector<std::pair<VkCommandBuffer, uint32_t>> oldBuffers_;
		bool dirty_ = false;
	};
}
