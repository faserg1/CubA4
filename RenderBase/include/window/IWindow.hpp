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
			virtual ~IWindow() = default;

			virtual SDL_Window *getSDLWindow() const = 0;
		protected:
			explicit IWindow() = default;
		private:
		};
	}
}

#endif // IWINDOW_HPP
