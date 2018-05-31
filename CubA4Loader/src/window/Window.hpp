#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <memory>
#include <window/IWindow.hpp>

namespace CubA4
{
	namespace window
	{
		class Window final :
			public virtual IWindow
		{
		public:
			static std::shared_ptr<Window> createWindow(int sizeX, int sizeY, int64_t additionalSDLWindowFlags);

			SDL_Window *getSDLWindow();
			bool isFullscreen();
			void setFullscreen(bool fullscreen);
			void toggleFullscreen();
		private:
			explicit Window(int sizeX, int sizeY, int64_t additionalSDLWindowFlags);
			~Window();

			bool fullscreenMode_;
			SDL_Window *window_;
		};
	}
}

#endif // WINDOW_HPP