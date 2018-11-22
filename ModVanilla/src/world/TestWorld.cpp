#include "./TestWorld.hpp"
using namespace CubA4::mod::world;

TestWorld::TestWorld()
{
	
}

TestWorld::~TestWorld()
{
	
}

std::string TestWorld::getId() const
{
	return "testWorld";
}

std::wstring TestWorld::getName() const
{
	return L"Тестовый мир";
}