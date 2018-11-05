#include "../../include/block/TestBlock.hpp"
using namespace CubA4::mod::block;

TestBlock::TestBlock(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel) :
	renderModel_(renderModel)
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

std::shared_ptr<const CubA4::render::engine::model::IRenderModel> TestBlock::getRenderModel() const
{
	return renderModel_;
}