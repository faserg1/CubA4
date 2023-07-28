#include <app/ServerMain.hpp>

int main(int argc, char *argv[])
{
	CubA4::app::ServerMain serverMain(argc, argv);
	return serverMain.exec();
}