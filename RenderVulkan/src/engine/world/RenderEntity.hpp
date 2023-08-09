#pragma once

#include <memory>
#include <functional>
#include <engine/pipeline/RenderFramebufferData.hpp>
#include <engine/model/EntityRenderModel.hpp>
#include <engine/material/Material.hpp>
#include <vector>
#include <map>
#include <vulkan/vulkan.h>
#include <engine/memory/IMemoryPart.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>
#include <engine/utils/EntityKeyHash.hpp>

namespace CubA4::render::engine::world
{
	class RenderEntity
	{
	public:
		using IdFactoryType = decltype(CubA4::object::WorldInfo::factoryId);
		using IdEntityType = decltype(CubA4::object::WorldInfo::entityId);
		using PairKey = std::pair<IdFactoryType, IdEntityType>;
		struct Data
		{
			using IMemoryPart = CubA4::render::engine::memory::IMemoryPart;
			VkCommandBuffer cmdBuffer;
			std::shared_ptr<const CubA4::render::engine::model::EntityRenderModel> renderModel;

			std::shared_ptr<void> intanceHostMemory;
			std::shared_ptr<const IMemoryPart> memoryHost;
			std::shared_ptr<const IMemoryPart> memoryDevice;
			vulkan::sVkBuffer instanceDeviceBuffer;
			vulkan::sVkBuffer instanceHostBuffer;
			VkDeviceSize bufferSize;
			
			std::unordered_map<PairKey, float*, CubA4::render::engine::utils::FactoryAndEntityIdHash> transforms_;

			CubA4::render::engine::pipeline::RenderFramebufferData data;
		};
	public:
		explicit RenderEntity(Data data, std::function<void()> deleter);
		~RenderEntity();

		bool exists(IdFactoryType factoryId, IdEntityType entityId) const;
		void executeFrom(VkCommandBuffer primaryCmdBuffer) const;

		const Data &getData() const;
		Data &getData();
	private:
		Data data_;
		std::function<void()> deleter_;
	};
}