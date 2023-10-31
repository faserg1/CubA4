#pragma once

#include <memory>

namespace CubA4::game
{
	class IGameControl;
}

namespace CubA4::mod
{
	class ModControl :
		public std::enable_shared_from_this<ModControl>
	{
	public:
		ModControl();
		virtual ~ModControl();
		void setGameControl(CubA4::game::IGameControl *gameControl);

		CubA4::game::IGameControl *getGameControl() const;
	private:
		CubA4::game::IGameControl *gameControl_ = nullptr;
	};
}