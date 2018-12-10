#ifndef MODVANILLA_MODRENDERMANAGER_HPP
#define MODVANILLA_MODRENDERMANAGER_HPP

#include <memory>
#include <manager/IModRenderManager.hpp>
#include <model/IRenderModelDefinition.hpp>
#include <map>
#include <string>

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
				std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout> getMaterialLayout(const std::string &id) const override;
				std::shared_ptr<const CubA4::render::engine::material::IMaterial> getMaterial(const std::string &id) const override;
				
				void registerRenderModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel);
				void registerMaterialLayout(std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout> renderMaterialLayout, const std::string &id);
				void registerMaterial(std::shared_ptr<const CubA4::render::engine::material::IMaterial> renderMaterial, const std::string &id);
			protected:
			private:
				std::map<std::string, std::shared_ptr<const CubA4::render::engine::model::IRenderModel>> modelMap_;
				std::map<std::string, std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout>> materialLayoutMap_;
				std::map<std::string, std::shared_ptr<const CubA4::render::engine::material::IMaterial>> materialMap_;
			};
		}
	}
}

#endif // MODVANILLA_MODRENDERMANAGER_HPP
