#pragma once

#include <memory>
#include <model/RenderModelData.hpp>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResource;
		}

		namespace model
		{
			class IModelReader
			{
			public:
				virtual ~IModelReader() = default;
				virtual core::model::RenderModelData readRenderModel(std::shared_ptr<const resources::IResource> resource) const = 0;
				virtual void writeRenderModel(std::shared_ptr<resources::IResource> resource, const core::model::RenderModelData &model) = 0;
			protected:
				explicit IModelReader() = default;
			};
		}
	}
}
