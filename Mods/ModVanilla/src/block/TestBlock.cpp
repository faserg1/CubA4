#include "../../include/block/TestBlock.hpp"
using namespace CubA4::block;

TestBlock::TestBlock(std::string id, std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef) :
	id_(id), modelDef_(modelDef)
{
	
}

TestBlock::~TestBlock()
{
	
}

std::string TestBlock::getId() const
{
	return id_;
}

std::wstring TestBlock::getName() const
{
	return L"Тестовый мать его блок!";
}

std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> TestBlock::getRenderModelDefinition() const
{
	return modelDef_;
}

const CubA4::physics::IBlockPhysicsDefinition &TestBlock::getPhysicsDefinition() const
{
	return blockPhysics_;
}

bool TestBlock::isMultilayered() const
{
	return false;
}
