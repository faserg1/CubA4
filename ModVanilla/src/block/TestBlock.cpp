#include "../../include/block/TestBlock.hpp"
using namespace CubA4::block;

TestBlock::TestBlock(std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef) :
	modelDef_(modelDef)
{
	
}

TestBlock::~TestBlock()
{
	
}

std::string TestBlock::getId() const
{
	return "testBlock";
}

std::wstring TestBlock::getName() const
{
	return L"Тестовый мать его блок!";
}

std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> TestBlock::getRenderModelDefinition() const
{
	return modelDef_;
}

bool TestBlock::isMultilayered() const
{
	return false;
}
