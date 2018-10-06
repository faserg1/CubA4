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
			class Memory;
		}

		namespace engine
		{
			namespace model
			{
				class ModelManager :
					public virtual IModelManager
				{
				public:
					explicit ModelManager();
					~ModelManager();

					void registerModel(const CubA4::core::model::IRenderModelDefinition &renderModel) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // MODELMANAGER_HPP
