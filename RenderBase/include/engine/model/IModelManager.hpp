#pragma once

#include <memory>
#include <model/IRenderModelDefinition.hpp>

namespace CubA4::render::engine::model
{
	class IRenderModel;

	class IModelManager
	{
	public:
		virtual std::shared_ptr<const IRenderModel> registerEntityModel(const CubA4::model::IRenderModelDefinition &renderModel) = 0;
	protected:
		explicit IModelManager() = default;
		virtual ~IModelManager() = default;
	private:
	};
}
