#pragma once

#include <atomic>
#include <engine/render/ISubRenderPipeline.hpp>
#include <engine/pipeline/IRenderEngineEntityPipelineSubscriber.hpp>
#include <util/ISubscription.hpp>
#include <tools/SpinLock.hpp>

namespace CubA4::render::engine::pipeline
{
	class RenderEntityPipeline;

	class EntitySubRenderPipeline :
		public virtual ISubRenderPipeline,
		public virtual IRenderEngineEntityPipelineSubscriber
	{
		struct OldEntitiesInfo
		{
			uint32_t cyclesLeft;
			std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderEntity>> oldEntities;
		};
	public:
		explicit EntitySubRenderPipeline(std::shared_ptr<RenderEntityPipeline> renderEntityPipeline, SubpipelineVersion incrementCount);
		~EntitySubRenderPipeline();

		void onIterate() override;
		void executeFrom(VkCommandBuffer primaryCmdBuffer) override;

		uint32_t getSubpass() const override;
		SubpipelineVersion getVersion() const override;

		void onRenderEntitiesUpdated(const std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderEntity>> &entities) override;
	private:
		uint32_t subpass_;
		const SubpipelineVersion incrementCount_;
		std::atomic<SubpipelineVersion> version_;

		std::vector<OldEntitiesInfo> oldEntities_;

		std::unique_ptr<CubA4::util::ISubscription> entityUpdateSubscription_;

		std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderEntity>> entities_;
		CubA4::render::tools::SpinLock entitiesLock_;
		CubA4::render::tools::SpinLock oldEntitiesLock_;
	};
}
