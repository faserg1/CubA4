#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include <memory>
#include <engine/IRenderManager.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			namespace material
			{
				class MaterialManager;
			}

			class RenderManager :
				public virtual IRenderManager
			{
			public:
				explicit RenderManager(std::shared_ptr<const vulkan::Device> device);
				~RenderManager();

				std::shared_ptr<material::IMaterialManager> getMaterialManager() const override;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				std::shared_ptr<material::MaterialManager> materialManager_;
			};
		}
	}
}

#endif // RENDERMANAGER_HPP
