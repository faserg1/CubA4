#include <world/TestDimensionDescription.hpp>
using namespace CubA4::world;

TestDimensionDescription::TestDimensionDescription() :
	worldGenerator_(std::make_unique<TestWorldGenerator>())
{

}

std::string TestDimensionDescription::getId() const
{
	return "testDimension";
}

std::wstring TestDimensionDescription::getName() const
{
	return L"Тестовое измерение";
}

std::shared_ptr<IWorldGenerator> TestDimensionDescription::getWorldGenerator() const
{
	return worldGenerator_;
}