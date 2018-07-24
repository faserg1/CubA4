#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

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
			namespace material
			{
				class ShaderFactory;
				class MaterialLayoutSetFactory;

				class MaterialManager :
					public virtual IMaterialManager
				{
				public:
					explicit MaterialManager(std::shared_ptr<const vulkan::Device> device);
					~MaterialManager();

					std::shared_ptr<IShaderFactory> getShaderFactory() const;
					std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory() const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					std::shared_ptr<ShaderFactory> shaderFactory_;
					std::shared_ptr<MaterialLayoutSetFactory> materialLayoutSetFactory_;
				};
			}
		}
	}
}

#endif // MATERIALMANAGER_HPP
