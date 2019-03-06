#ifndef MODBASE_IMODRENDERMANAGER_HPP
#define MODBASE_IMODRENDERMANAGER_HPP

#include <memory>
#include <string>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialLayout;
				class IMaterial;
				class ITexture;
			}

			namespace model
			{
				class IRenderModel;
			}
		}
	}

	namespace mod
	{
		namespace manager
		{
			class IModRenderManager
			{
			public:
				virtual std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getModel(const std::string &id) const = 0;
				virtual std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout> getMaterialLayout(const std::string &id) const = 0;
				virtual std::shared_ptr<const CubA4::render::engine::material::IMaterial> getMaterial(const std::string &id) const = 0;
				virtual std::shared_ptr<const CubA4::render::engine::material::ITexture> getTexture(const std::string &id) const = 0;
			protected:
				explicit IModRenderManager() = default;
				virtual ~IModRenderManager() = default;
			private:
			};
		}
	}
}

#endif // MODBASE_IMODRENDERMANAGER_HPP
