#pragma once

#include <memory>
#include <vulkan/Device.hpp>
#include <engine/memory/MemoryManager.hpp>
#include <engine/memory/MemoryHelper.hpp>
#include <engine/model/RenderModel.hpp>
#include <engine/world/RenderEntity.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/Transform.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <vulkan/RenderPass.hpp>
#include <engine/RenderManager.hpp>
#include <engine/pipeline/RenderFramebufferData.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>

namespace CubA4
{
	class ICore;
}

namespace CubA4::render::engine::pipeline
{
	struct EntityInfo
	{
		const CubA4::object::Transform &transform;
		decltype(CubA4::object::WorldInfo::factoryId) factoryId;
		decltype(CubA4::object::WorldInfo::entityId) entityId;
	};

	class RenderEntityCompiler
	{
		
		using RenderEntity = CubA4::render::engine::world::RenderEntity;
		using Data = RenderEntity::Data;
	public:
		RenderEntityCompiler(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const vulkan::RenderPass> renderPass, std::shared_ptr<RenderManager> renderManager, uint32_t subpassNumber);

		uint32_t getSubpassNumber() const;

		std::shared_ptr<RenderEntity> createEntity(std::vector<EntityInfo> infos,
			const CubA4::object::RenderInfoComponent &render, const RenderFramebufferData &data);
		std::shared_ptr<RenderEntity> extendEntity(std::shared_ptr<RenderEntity> entity, std::vector<EntityInfo> infos,
			const CubA4::object::RenderInfoComponent &render, const RenderFramebufferData &data);
		std::shared_ptr<RenderEntity> shrinkEntity(std::vector<EntityInfo> infos,
			const CubA4::object::RenderInfoComponent &render, const RenderFramebufferData &data);

		void updateEntity(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, RenderEntity &entity);

		std::shared_ptr<RenderEntity> recompileEntity(std::shared_ptr<RenderEntity> entity, const RenderFramebufferData &data);
	private:
		void recordCmdBuffer(Data &data, const RenderFramebufferData &framebufferData);
		void createIntancesBuffer(Data &data, size_t entityCount);
		void updateTransforms(const CubA4::object::Transform &tr, float *mat4x4);
	private:
		const std::shared_ptr<const ICore> core_;
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const vulkan::RenderPass> renderPass_;
		const std::shared_ptr<RenderManager> renderManager_;
		const std::shared_ptr<const world::WorldManager> worldManager_;
		const uint32_t subpassNumber_;
		const std::unique_ptr<CubA4::render::engine::memory::MemoryManager> memoryManager_;
		const std::unique_ptr<CubA4::render::engine::memory::MemoryHelper> memoryHelper_;

		std::shared_ptr<vulkan::CommandPool> commandPool_;
	};
}