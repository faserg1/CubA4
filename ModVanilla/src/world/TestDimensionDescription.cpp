#include <world/TestDimensionDescription.hpp>
using namespace CubA4::world;

TestDimensionDescription::TestDimensionDescription(const CubA4::ICore &core, const manager::ModBlockManager &blockManager) :
	worldGenerator_(std::make_unique<TestWorldGenerator>(core, blockManager))
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

const CubA4::physics::IPhysicsDefinition &TestDimensionDescription::getPhysicsDefinition() const
{
	return physics_;
}