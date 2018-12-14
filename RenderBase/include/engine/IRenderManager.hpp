#ifndef RENDERBASE_IRENDERMANAGER_HPP
#define RENDERBASE_IRENDERMANAGER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
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
			protected:
				explicit IRenderManager() = default;
				virtual ~IRenderManager() = default;
			private:
			};
		}
	}
}

#endif // RENDERBASE_IRENDERMANAGER_HPP
