#ifndef MODVANILLA_MODMANAGER_HPP
#define MODVANILLA_MODMANAGER_HPP

#include <memory>
#include <manager/IModManager.hpp>

namespace CubA4
{
	namespace mod
	{
		namespace manager
		{
			class ModRenderManager;

			class ModManager :
				public virtual IModManager
			{
			public:
				explicit ModManager();
				~ModManager();

				std::weak_ptr<const IModRenderManager> getModRenderManager() const override;
				std::shared_ptr<ModRenderManager> getModRenderManager();
			protected:
			private:
				const std::shared_ptr<ModRenderManager> renderManager_;
			};
		}
	}
}

#endif // MODVANILLA_MODMANAGER_HPP
