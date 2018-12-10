#ifndef RENDERVULKAN_SHADERFACTORY_HPP
#define RENDERVULKAN_SHADERFACTORY_HPP

#include <memory>
#include <string>
#include <engine/material/IShaderFactory.hpp>

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
				class ShaderFactory :
					public virtual IShaderFactory
				{
				public:
					explicit ShaderFactory(std::shared_ptr<const vulkan::Device> device);
					~ShaderFactory();

					std::shared_ptr<const IShader> createFromBinary(const void *data, size_t size, ShaderType type, std::string entryPoint) const override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_SHADERFACTORY_HPP
