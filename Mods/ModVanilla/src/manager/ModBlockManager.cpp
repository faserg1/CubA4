#include <manager/ModBlockManager.hpp>
using namespace CubA4::manager;

ModBlockManager::ModBlockManager()
{
	
}

ModBlockManager::~ModBlockManager()
{
	
}

std::shared_ptr<CubA4::model::IBlockRenderModelDefinition> ModBlockManager::getBlockDefinition(const std::string &id) const
{
	if (auto result = defs_.find(id); result != defs_.end())
		return result->second;
	return {};
}

void ModBlockManager::addBlockDefinition(const std::string &id, std::shared_ptr<CubA4::model::IBlockRenderModelDefinition> def)
{
	defs_.insert(std::make_pair(id, def));
}

std::shared_ptr<CubA4::object::IBlock> ModBlockManager::getBlock(const std::string &id) const
{
	if (auto result = blocks_.find(id); result != blocks_.end())
		return result->second;
	return {};
}

void ModBlockManager::addBlock(std::shared_ptr<CubA4::object::IBlock> block)
{
	blocks_.insert(std::make_pair(block->getId(), block));
}