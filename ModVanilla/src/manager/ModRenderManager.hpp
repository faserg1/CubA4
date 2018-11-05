#ifndef MODRENDERMANAGER_HPP
#define MODRENDERMANAGER_HPP

#include <memory>
#include <manager/IModRenderManager.hpp>
#include <model/IRenderModelDefinition.hpp>
#include <map>

namespace CubA4
{
	namespace mod
	{
		namespace manager
		{
			class ModRenderManager :
				public virtual IModRenderManager
			{
			public:
				explicit ModRenderManager();
				~ModRenderManager();

				std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getModel(const std::string &id) const override;
				void registerRenderModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel);
			protected:
			private:
				std::map<std::string, std::shared_ptr<const CubA4::render::engine::model::IRenderModel>> map_;
			};
		}
	}
}

#endif // MODRENDERMANAGER_HPP
