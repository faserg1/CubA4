#include <world/TestWorldDefinition.hpp>
using namespace CubA4::world;

TestWorldDefinition::TestWorldDefinition() :
	testDimensionDescription_(std::make_unique<TestDimensionDescription>())
{
	descriptions_.push_back(*testDimensionDescription_.get());	
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

const TestWorldDefinition::DimensionDescriptionCollection &TestWorldDefinition::getDimensionDescriptions() const
{
	return descriptions_;
}