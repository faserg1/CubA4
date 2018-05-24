#ifndef IRENDERENGINE_HPP
#define IRENDERENGINE_HPP

#include <memory>

namespace CubA4
{
	namespace window
	{
		class IWindow;
	}

	namespace render
	{
		namespace engine
		{
			class IRenderEngine
			{
			public:
				virtual ~IRenderEngine() {}

				virtual void init(std::shared_ptr<window::IWindow> window) = 0;
				virtual void destroy() = 0;
			protected:
				explicit IRenderEngine() {}
			private:
			};
		}
	}
}

#endif // IRENDERENGINE_HPP
