#pragma once

#include <model/IModelFactory.hpp>
#include <model/IModelReader.hpp>

namespace CubA4:: model
{
	class ModelFactory : public virtual IModelFactory
	{
	public:
		explicit ModelFactory();
		~ModelFactory();

		std::shared_ptr<IBlockRenderModelDefinition> createSimpleBlockRenderModelDefinition(
			const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const override;
		std::shared_ptr<IRenderModelDefinition> createSimpleRenderModelDefinition(
			const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const override;
	private:
		std::shared_ptr<IModelReader> reader_;
	};
}

