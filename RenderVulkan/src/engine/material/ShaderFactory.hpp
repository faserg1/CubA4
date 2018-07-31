#ifndef SHADERFACTORY_HPP
#define SHADERFACTORY_HPP

#include <memory>
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

					std::shared_ptr<IShader> createFromBinary(const void *data, size_t size, ShaderType type) const override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
				};
			}
		}
	}
}

#endif // SHADERFACTORY_HPP