#include <startup/BlockSetup.hpp>
#include <block/TestBlock.hpp>
using namespace CubA4::startup;
using namespace CubA4::logging;

BlockSetup::BlockSetup() = default;
BlockSetup::~BlockSetup() = default;

void BlockSetup::load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager)
{
	core_ = core;
	manager_ = manager;
	log_ = core->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/BlockSetup");
}

void BlockSetup::init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{
	auto blockManager = manager_->getBlockManager();
	auto def = blockManager->getBlockDefinition("test");
	auto testBlock = std::make_shared<block::TestBlock>(def);
	blockManager->addBlock("test", testBlock);
}
