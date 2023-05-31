#pragma once

#include <memory>

namespace CubA4::render
{
	namespace ui
	{
		class IUIManager;
	}

	namespace engine
	{
		namespace material
		{
			class IMaterialManager;
		}

		namespace model
		{
			class IModelManager;
		}

		namespace world
		{
			class IWorldManager;
		}

		/// Класс взаимодействия с рендер миром
		class IRenderManager
		{
		public:
			virtual std::shared_ptr<material::IMaterialManager> getMaterialManager() const = 0;
			virtual std::shared_ptr<model::IModelManager> getModelManager() const = 0;
			virtual std::shared_ptr<world::IWorldManager> getWorldManager() const = 0;
			virtual std::shared_ptr<CubA4::render::ui::IUIManager> getUIManager() const = 0;
		protected:
			explicit IRenderManager() = default;
			virtual ~IRenderManager() = default;
		private:
		};
	}
}
