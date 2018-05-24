#ifndef IWINDOW_HPP
#define IWINDOW_HPP

struct SDL_Window;

namespace CubA4
{
	namespace window
	{
		class IWindow
		{
		public:
			virtual ~IWindow() {}

			virtual SDL_Window *getSDLWindow() = 0;
		protected:
			explicit IWindow() {}
		private:
		};
	}
}

#endif // IWINDOW_HPP
