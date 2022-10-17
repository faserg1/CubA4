#pragma once

#include <memory>
#include <engine/model/IModelManager.hpp>

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
				public:
					explicit ModelManager(std::shared_ptr<const vulkan::Device> device);
					~ModelManager();

					std::shared_ptr<const IRenderModel> registerModel(const CubA4::mod::model::IRenderModelDefinition &renderModelDef) override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryAllocator> allocator_;
					std::shared_ptr<memory::MemoryHelper> memoryHelper_;
				};
			}
		}
	}
}
