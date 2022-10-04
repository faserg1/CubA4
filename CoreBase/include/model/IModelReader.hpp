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
				virtual mod::model::RenderModelData readRenderModel(std::shared_ptr<resources::IResource> resource) = 0;
			protected:
				explicit IModelReader() = default;
			};
		}
	}
}
