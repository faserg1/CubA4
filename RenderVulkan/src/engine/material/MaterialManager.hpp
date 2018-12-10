#ifndef RENDERVULKAN_MATERIALMANAGER_HPP
#define RENDERVULKAN_MATERIALMANAGER_HPP

#include <memory>
#include <engine/material/IMaterialManager.hpp>

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
			class Render;
			class ResourceManager;

			namespace material
			{
				class ShaderFactory;
				class MaterialLayoutSetFactory;
				class MaterialFactory;

				class MaterialManager :
					public virtual IMaterialManager
				{
				public:
					explicit MaterialManager(std::shared_ptr<const vulkan::Device> device,
						std::shared_ptr<const Render> render,
						std::shared_ptr<ResourceManager> resourceManager);
					~MaterialManager();

					std::shared_ptr<IShaderFactory> getShaderFactory() const override;
					std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory() const override;
					std::shared_ptr<IMaterialFactory> getMaterialFactory() const override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const Render> render_;
					const std::shared_ptr<ResourceManager> resourceManager_;
					std::shared_ptr<ShaderFactory> shaderFactory_;
					std::shared_ptr<MaterialFactory> materialFactory_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALMANAGER_HPP
