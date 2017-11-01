#ifndef RENDER_INFO_HPP
#define RENDER_INFO_HPP

#include <cstdint>
#include <string>

namespace CubA4
{
	namespace render
	{
		class RenderEngine;

		class RenderInfo
		{
		public:
			virtual ~RenderInfo() {}
			virtual std::string getRenderEngineName() const = 0;
			virtual RenderEngine *getRenderEngine() = 0;
			//virtual int64_t getSDLWindowFlags() = 0;
		};
	}
}

#endif // RENDER_INFO_HPP