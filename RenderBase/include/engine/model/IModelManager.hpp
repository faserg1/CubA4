#ifndef IMODELMANAGER_HPP
#define IMODELMANAGER_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IRenderModelDefinition;
		}
	}

	namespace render
	{
		namespace engine
		{
			namespace model
			{
				class IRenderModel;

				class IModelManager
				{
				public:
					virtual std::shared_ptr<const IRenderModel> registerModel(const CubA4::core::model::IRenderModelDefinition &renderModel) = 0;
				protected:
					explicit IModelManager() = default;
					virtual ~IModelManager() = default;
				private:
				};
			}
		}
	}
}

#endif // IMODELMANAGER_HPP
