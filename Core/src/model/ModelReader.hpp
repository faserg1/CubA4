#pragma once

#include <model/IModelReader.hpp>


namespace CubA4::model
{
	class ModelReader : public virtual IModelReader
	{
	public:
		explicit ModelReader();
		~ModelReader();

		RenderModelData readRenderModel(std::shared_ptr<const resources::IResource> resource) const override;
		void writeRenderModel(std::shared_ptr<resources::IResource> resource, const RenderModelData &model) override;
	};
}
