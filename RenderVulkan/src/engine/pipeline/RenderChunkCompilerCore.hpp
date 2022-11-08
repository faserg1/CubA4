#pragma once

#include <memory>
#include <vector>
#include <map>

#include <world/IChunk.hpp>
#include <model/IBlockRenderModelDefinition.hpp>
#include <engine/model/RenderModel.hpp>
#include <engine/material/Material.hpp>

#include <vulkan/Device.hpp>
#include <vulkan/Memory.hpp>
#include <vulkan/CommandPool.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace memory
			{
				class MemoryAllocator;
				class MemoryManager;
			}

			namespace pipeline
			{
				class RenderChunkCompilerCore
				{
					using BlockPtr = std::shared_ptr<const CubA4::object::IBlock>;
					using MaterialPtr = std::shared_ptr<const CubA4::render::engine::material::Material>;
					using ModelDefPtr = std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition>;
					using HiddenSides = std::array<CubA4::world::BlockSides, CubA4::world::ChunkSize*CubA4::world::ChunkSize*CubA4::world::ChunkSize>;
					using RenderModelPtr = std::shared_ptr<const CubA4::render::engine::model::RenderModel>;
					using RenderModels = std::map<MaterialPtr, std::shared_ptr<const CubA4::render::engine::model::RenderModel>>;
				public:
				protected:
					explicit RenderChunkCompilerCore(std::shared_ptr<const vulkan::Device> device);
					~RenderChunkCompilerCore();

					std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> lockCommandPool();
					vulkan::sVkDescriptorPool getDescriptorPool(const std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> &lock);
					RenderModels compileBlocks(std::shared_ptr<const CubA4::world::IChunk> chunk);
					RenderModelPtr compileModelByMaterial(std::shared_ptr<const CubA4::world::IChunk> chunk, const std::string &material, std::vector<BlockPtr> blocks, const HiddenSides &hiddenSides);
					HiddenSides compileHiddenSides(std::shared_ptr<const CubA4::world::IChunk> chunk) const;
				protected:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryManager> memManager_;
				private:					
					std::vector<std::shared_ptr<vulkan::CommandPool>> commandPools_;
					std::vector<vulkan::sVkDescriptorPool> descriptorPools_;
				private:
					void initCommandPools();
					void initDescriptorPools();
				};
			}
		}
	}
}

