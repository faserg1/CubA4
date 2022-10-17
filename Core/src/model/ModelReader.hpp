#pragma once

#include <model/IModelReader.hpp>


namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class ModelReader : public virtual IModelReader
			{
			public:
				explicit ModelReader();
				~ModelReader();

				CubA4::core::model::RenderModelData readRenderModel(std::shared_ptr<const resources::IResource> resource) const override;
				void writeRenderModel(std::shared_ptr<resources::IResource> resource, const core::model::RenderModelData &model) override;
			};
		}
	}
}
