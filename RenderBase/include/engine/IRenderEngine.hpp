#ifndef RENDERBASE_IRENDERENGINE_HPP
#define RENDERBASE_IRENDERENGINE_HPP

#include <memory>

namespace CubA4
{
	namespace window
	{
		class IWindow;
	}

	namespace core
	{
		namespace game
		{
			class IGame;
		}
	}

	namespace render
	{
		namespace engine
		{
			class IRenderManager;

			class IRenderEngine
			{
			public:
				virtual ~IRenderEngine() = default;

				virtual void init(std::shared_ptr<const window::IWindow> window) = 0;
				virtual void destroy() = 0;

				virtual void setGame(std::shared_ptr<const CubA4::core::game::IGame> game) = 0;

				virtual void run() = 0;
				virtual void stop() = 0;

				virtual std::shared_ptr<IRenderManager> getRenderManager() const = 0;
			protected:
				explicit IRenderEngine() = default;
			private:
			};
		}
	}
}

#endif // RENDERBASE_IRENDERENGINE_HPP
