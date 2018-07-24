#ifndef VERTEXSHADER_HPP
#define VERTEXSHADER_HPP

#include "Shader.hpp"
#include <engine/material/IVertexShader.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class VertexShader :
					public Shader, public virtual IVertexShader
				{
				public:
					explicit VertexShader(std::shared_ptr<const vulkan::Device> device, VkShaderModule shaderModule);
					~VertexShader();

					ShaderType getType() const override final;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VERTEXSHADER_HPP
