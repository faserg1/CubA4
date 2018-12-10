#ifndef CUBA4LOADER_WINDOW_HPP
#define CUBA4LOADER_WINDOW_HPP

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
			static std::shared_ptr<Window> createWindow(int sizeX, int sizeY, uint32_t additionalSDLWindowFlags);

			SDL_Window *getSDLWindow() const override;
			bool isFullscreen();
			void setFullscreen(bool fullscreen);
			void toggleFullscreen();
		private:
			explicit Window(int sizeX, int sizeY, uint32_t additionalSDLWindowFlags);
			~Window();

			bool fullscreenMode_;
			///Оригинальное SDL окно
			SDL_Window *window_;
		};
	}
}

#endif // CUBA4LOADER_WINDOW_HPP