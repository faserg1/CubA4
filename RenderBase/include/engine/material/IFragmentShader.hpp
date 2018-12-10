#ifndef RENDERBASE_IFRAGMENTSHADER_HPP
#define RENDERBASE_IFRAGMENTSHADER_HPP

#include "IShader.hpp"

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IFragmentShader :
					public virtual IShader
				{
				public:
					virtual ~IFragmentShader() = default;
				protected:
					explicit IFragmentShader() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_IFRAGMENTSHADER_HPP
