#ifndef SHADER_HPP 
#define SHADER_HPP 

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device; 
			 
			class Shader 
			{
			public:
				VkShaderModule getModule() const;

				static std::shared_ptr<Shader > fromIrs(std::shared_ptr<Device > device, const char *name);
			protected:
				explicit Shader(std::shared_ptr<Device> device, const void *data, size_t size);
				~Shader();
			private:
				std::shared_ptr<Device> device_;
				VkShaderModule module_;
			};
		}
	}
}

#endif // SHADER_HPP 
