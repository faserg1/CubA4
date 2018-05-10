#ifndef IRENDER_ENGINE_HPP
#define IRENDER_ENGINE_HPP

namespace CubA4
{
	namespace render
	{
		class IRenderEngine
		{
		public:
			virtual ~IRenderEngine() {}
		protected:
			explicit IRenderEngine() {}
		};
	}
}

#endif // IRENDER_ENGINE_HPP