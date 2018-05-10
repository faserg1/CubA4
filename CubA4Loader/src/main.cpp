#include <SDL.h>
#include <stdexcept>
#include "./app/CubA4Main.hpp"

int main(int argc, char *argv[])
{
	CubA4::app::AppMain appMain;

	return appMain.exec();
}