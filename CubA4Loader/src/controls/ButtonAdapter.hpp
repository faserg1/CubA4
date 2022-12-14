#pragma once

#include <SDL.h>
#include <game/controller/Buttons.hpp>

namespace CubA4::controls
{
	class ButtonAdapter
	{
	public:
		static SDL_Scancode adapt(CubA4::game::controller::Button button);
		static CubA4::game::controller::Button adapt(SDL_Scancode scancode);
		static CubA4::game::controller::Button adaptMouse(uint8_t btn);
		static CubA4::game::controller::BMods adapt(uint16_t mod);
	};
}
