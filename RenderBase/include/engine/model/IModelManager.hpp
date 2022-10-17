#pragma once

#include <memory>
#include <model/IRenderModelDefinition.hpp>

namespace CubA4
{
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
					virtual std::shared_ptr<const IRenderModel> registerModel(const CubA4::mod::model::IRenderModelDefinition &renderModel) = 0;
				protected:
					explicit IModelManager() = default;
					virtual ~IModelManager() = default;
				private:
				};
			}
		}
	}
}

