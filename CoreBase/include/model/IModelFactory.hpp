#pragma once

#include <model/IModelDefinition.hpp>
#include <model/IRenderModelDefinition.hpp>
#include <memory>

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
			class IModelFactory
			{
			public:
				virtual ~IModelFactory() = default;

				virtual std::shared_ptr<mod::model::IRenderModelDefinition> createSimpleRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model) const = 0;
			protected:
				explicit IModelFactory() = default;
			};
		}
	}
}
