#include <ModControl.hpp>
using namespace CubA4::mod;

ModControl::ModControl() = default;
ModControl::~ModControl() = default;

void ModControl::setGameControl(CubA4::game::IGameControl *gameControl)
{
	gameControl_ = gameControl;
}

CubA4::game::IGameControl *ModControl::getGameControl() const
{
	return gameControl_;
}