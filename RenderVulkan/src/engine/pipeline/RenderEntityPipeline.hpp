#pragma once

#include <ICore.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/RenderPass.hpp>
#include <engine/pipeline/IRenderEngineEntityPipeline.hpp>
#include <engine/pipeline/IRenderEngineEntityPipelineSubscriber.hpp>
#include <engine/RenderManager.hpp>
#include <engine/utils/EntityKeyHash.hpp>
#include <util/SubscriptionHelper.hpp>
#include <memory>

namespace CubA4::object
{
	struct Transform;
	struct WorldInfo;
	struct RenderInfoComponent;
}

namespace CubA4::render::engine::world
{
	class RenderEntity;
}

namespace CubA4::render::engine::pipeline
{
	class RenderEntityCompiler;

	class RenderEntityPipeline : public virtual IRenderEngineEntityPipeline
	{
		using RenderEntity = CubA4::render::engine::world::RenderEntity;
	public:
		RenderEntityPipeline(std::shared_ptr<RenderEntityCompiler> entityCompiler);

		void onFramebufferUpdated(const RenderFramebufferData &data) override;

		uint32_t getSubpassNumber() const;

		void onEntityAdded(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) override;
		void onEntityUpdated(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) override;
		void onEntityRemoved(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) override;

		std::unique_ptr<CubA4::util::ISubscription> subscribe(IRenderEngineEntityPipelineSubscriber *subscriber);
	private:
		std::shared_ptr<RenderEntityCompiler> entityCompiler_;
		std::unordered_map<std::string, std::shared_ptr<RenderEntity>> entities_;
		
		RenderFramebufferData framebufferData;
		CubA4::util::SubscriptionHelper<IRenderEngineEntityPipelineSubscriber> subHelper_;
		/*
			renderEntities 
			  -- models (material)
			  -- map<id, transformation>

			builder (all renderEntities, new tr, wi, ric)
				-- find same or create render entts
				-- add id->tr
				-- record command buffer with instancing
				-- input rate instance (create new pipeline)
				-- new vertex buffer (instance rate) <= copy all transformation
		*/
	};
}