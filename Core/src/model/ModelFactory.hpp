#pragma once

#include <model/IModelFactory.hpp>
#include <model/IModelReader.hpp>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class ModelFactory : public virtual IModelFactory
			{
			public:
				explicit ModelFactory();
				~ModelFactory();

				std::shared_ptr<mod::model::IRenderModelDefinition> createSimpleRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model) const override;
			private:
				std::shared_ptr<IModelReader> reader_;
			};
		}
	}
}
