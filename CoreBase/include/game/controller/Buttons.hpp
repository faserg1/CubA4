#pragma once

#include <cstdint>
#include <util/Enums.hpp>

namespace CubA4::game::controller
{
	enum class AxisBinding : uint32_t
	{
		MOUSE = 1,
	};

	enum class Button : uint32_t
	{
		None, /// < There are no real buton here
		N0,
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		ALeft,
		ARight,
		AUp,
		ADown,
		CtrlLeft,
		CtrlRight,
		Space,
		Enter,
		Backspace,
		Escape,
		Tab,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		LMB,
		RMB,
		MMB,
		MScrollDown,
		MScrollUp
	};

	enum class BMod : uint16_t
	{
		None = 0,
		Any = 0x1,
		LShift = 0x2,
		RShift = 0x4,
		LAlt = 0x8,
		RAlt = 0x10,
		LCtrl = 0x20,
		RCtrl = 0x40
	};

	CUBA4_ENUM_FLAGS_OPERATORS(BMod, BMods, uint16_t);
}