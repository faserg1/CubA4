#ifndef IVERTEXSHADER_HPP
#define IVERTEXSHADER_HPP

#include "IShader.hpp"

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IVertexShader :
					public virtual IShader
				{
				public:
					virtual ~IVertexShader() {}
				protected:
					explicit IVertexShader() {}
				private:
				};
			}
		}
	}
}

#endif // IVERTEXSHADER_HPP
