#ifndef SHADER_HPP
#define SHADER_HPP

#include <engine/material/IShader.hpp>
#include <vulkan/vulkan.h>
#include <memory>

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
				class Shader :
					public virtual IShader
				{
				public:
					
				protected:
					explicit Shader(std::shared_ptr<vulkan::Device> device, VkShaderModule shaderModule);
					~Shader();
				private:
					const std::shared_ptr<vulkan::Device> device_;
					VkShaderModule shaderModule_;
				};
			}
		}
	}
}

#endif // SHADER_HPP
