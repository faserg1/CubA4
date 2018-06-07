#include <SDL.h> //sdl main
#include "./app/CubA4Main.hpp"

int main(int argc, char *argv[])
{
	CubA4::app::AppMain appMain(argc, argv);
	return appMain.exec();
}