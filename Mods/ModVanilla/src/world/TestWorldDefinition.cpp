#include <world/TestWorldDefinition.hpp>
using namespace CubA4::world;

TestWorldDefinition::TestWorldDefinition(const CubA4::ICore &core, const manager::ModBlockManager &blockManager) :
	testDimensionDescription_(std::make_unique<TestDimensionDescription>(core, blockManager))
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