#ifndef MODELMANAGER_HPP
#define MODELMANAGER_HPP

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
			class MemoryAllocator;
			class MemoryManager;

			namespace model
			{
				class ModelManager :
					public virtual IModelManager
				{
				public:
					explicit ModelManager(std::shared_ptr<const vulkan::Device> device);
					~ModelManager();

					std::shared_ptr<const IRenderModel> registerModel(const CubA4::core::model::IRenderModelDefinition &renderModelDef) override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<MemoryAllocator> allocator_;
					std::shared_ptr<MemoryManager> memoryManager_;
				};
			}
		}
	}
}

#endif // MODELMANAGER_HPP
