#pragma once

#include <memory>
#include <engine/model/IModelManager.hpp>
#include "./RenderModel.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			namespace memory
			{
				class MemoryAllocator;
				class MemoryHelper;
			}

			namespace model
			{
				class ModelManager :
					public virtual IModelManager
				{
					using Vertex = CubA4::model::Vertex;
					using UVWCoords = CubA4::model::UVWCoords;
					using FaceIndices = CubA4::model::FaceIndices;
				public:
					explicit ModelManager(std::shared_ptr<const vulkan::Device> device);
					~ModelManager();

					std::shared_ptr<const IRenderModel> registerModel(const CubA4::model::IRenderModelDefinition &renderModelDef) override;
					std::shared_ptr<const RenderModel> createModel(const CubA4::model::IRenderModelDefinition &renderModelDef);
				protected:
					std::shared_ptr<const RenderModel> createModel(std::string id, const std::vector<Vertex> &vertices, const std::vector<UVWCoords> &uvws, const FaceIndices &faces);
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryAllocator> allocator_;
					std::shared_ptr<memory::MemoryHelper> memoryHelper_;
				};
			}
		}
	}
}
