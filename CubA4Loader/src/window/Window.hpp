#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstdint>
#include <memory>

struct SDL_Window;

namespace CubA4
{
	namespace window
	{
		class Window final
		{
		public:
			static std::shared_ptr<Window> createWindow(int sizeX, int sizeY, int64_t additionalSDLWindowFlags);

			SDL_Window *getSDLWindow();
		private:
			explicit Window(int sizeX, int sizeY, int64_t additionalSDLWindowFlags);
			~Window();

			SDL_Window *window_;
		};
	}
}

#endif // WINDOW_HPP