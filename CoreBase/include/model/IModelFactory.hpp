#pragma once

#include <resources/IResource.hpp>
#include <model/IModelDefinition.hpp>
#include <model/IRenderModelDefinition.hpp>
#include <model/IBlockRenderModelDefinition.hpp>
#include <memory>
#include <map>

namespace CubA4::model
{
	class IModelFactory
	{
	public:
		virtual ~IModelFactory() = default;
		using RMaterialsMap = std::map<std::string, IBlockRenderModelDefinition::RMaterial>;

		virtual std::shared_ptr<IBlockRenderModelDefinition> createSimpleBlockRenderModelDefinition(
			const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const = 0;
		virtual std::shared_ptr<IRenderModelDefinition> createSimpleRenderModelDefinition(
			const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const = 0;
	protected:
		explicit IModelFactory() = default;
	};
}
