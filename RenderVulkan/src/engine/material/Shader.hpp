#ifndef RENDERVULKAN_SHADER_HPP
#define RENDERVULKAN_SHADER_HPP

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
					VkShaderModule getShaderModule() const;
					const std::string &getEntryPoint() const override;
				protected:
					explicit Shader(std::shared_ptr<const vulkan::Device> device, VkShaderModule shaderModule, std::string entryPoint);
					~Shader();
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const VkShaderModule shaderModule_;
					const std::string entryPoint_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_SHADER_HPP
