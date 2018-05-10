#ifndef IRENDER_INFO_HPP
#define IRENDER_INFO_HPP

#include <cstdint>
#include <string>

namespace CubA4
{
	namespace render
	{
		class IRenderEngine;

		class IRenderInfo
		{
		public:
			virtual ~IRenderInfo() {}
			virtual std::string getRenderEngineId() const = 0;
			virtual IRenderEngine *getRenderEngine() = 0;
			virtual int64_t getSDLWindowFlags() const = 0;
		protected:
			explicit IRenderInfo() {}
		};
	}
}

#endif // IRENDER_INFO_HPP