#pragma once

#include <cstdint>
#include <memory>
#include <window/IWindow.hpp>

namespace CubA4::window
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
	private:
		const uint32_t flags_;
		bool fullscreenMode_;

		struct {
			int x;
			int y;
			int sizeX;
			int sizeY;
		} savedCoords_;

		///Оригинальное SDL окно
		SDL_Window *window_;
	};
}

