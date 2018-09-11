#ifndef ISHADER_HPP
#define ISHADER_HPP

#include <string>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				enum class ShaderType
				{
					Vertex,
					Fragment
				};

				class IShader
				{
				public:
					virtual ~IShader() = default;

					virtual ShaderType getType() const = 0;
					virtual const std::string &getEntryPoint() const = 0;
				protected:
					explicit IShader() = default;
				private:
				};
			}
		}
	}
}

#endif // ISHADER_HPP
