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

void BlockSetup::init(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	auto blockManager = manager_->getBlockManager();
	auto def1 = blockManager->getBlockDefinition("test1");
	auto testBlock1 = std::make_shared<block::TestBlock>("testBlock1", def1);
	blockManager->addBlock(testBlock1);
	builder->registerObject(testBlock1);

	auto def2 = blockManager->getBlockDefinition("test2");
	auto testBlock2 = std::make_shared<block::TestBlock>("testBlock2", def2);
	blockManager->addBlock(testBlock2);
	builder->registerObject(testBlock2);
}
