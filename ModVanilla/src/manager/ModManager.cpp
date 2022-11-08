#include <manager/ModManager.hpp>
using namespace CubA4::manager;

ModManager::ModManager()
{
	blockManager_ = std::make_shared<ModBlockManager>();
}

ModManager::~ModManager()
{
	
}

std::shared_ptr<const IModBlockManager> ModManager::getBlockManager() const
{
	return blockManager_;
}

std::shared_ptr<ModBlockManager> ModManager::getBlockManager()
{
	return blockManager_;
}