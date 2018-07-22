#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include "Shader.hpp"
#include <engine/material/IFragmentShader.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class FragmentShader :
					public Shader, public virtual IFragmentShader
				{
				public:
					explicit FragmentShader(std::shared_ptr<vulkan::Device> device, VkShaderModule shaderModule);
					~FragmentShader();

					ShaderType getType() const override final;
				protected:
				private:
				};
			}
		}
	}
}

#endif // FRAGMENTSHADER_HPP
