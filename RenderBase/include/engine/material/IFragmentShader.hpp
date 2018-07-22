#ifndef IFRAGMENTSHADER_HPP
#define IFRAGMENTSHADER_HPP

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
					virtual ~IFragmentShader() {}
				protected:
					explicit IFragmentShader() {}
				private:
				};
			}
		}
	}
}

#endif // IFRAGMENTSHADER_HPP
