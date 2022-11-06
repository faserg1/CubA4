#pragma once

#include <resources/IResource.hpp>
#include <model/IModelDefinition.hpp>
#include <model/IBlockRenderModelDefinition.hpp>
#include <memory>

namespace CubA4::model
{
	class IModelFactory
	{
	public:
		virtual ~IModelFactory() = default;

		virtual std::shared_ptr<IBlockRenderModelDefinition> createSimpleBlockRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model) const = 0;
	protected:
		explicit IModelFactory() = default;
	};
}
