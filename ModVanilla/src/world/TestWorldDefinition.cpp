#include <world/TestWorldDefinition.hpp>
using namespace CubA4::world;

TestWorldDefinition::TestWorldDefinition()
{
	
}

TestWorldDefinition::~TestWorldDefinition()
{
	
}

std::string TestWorldDefinition::getId() const
{
	return "testWorld";
}

std::wstring TestWorldDefinition::getName() const
{
	return L"Тестовый мир";
}