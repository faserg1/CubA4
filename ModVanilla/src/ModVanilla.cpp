#include "ModVanilla.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <ModVanillaConst.hpp>
#include <fmt/format.h>
#include <audio/IAudioImporter.hpp>
#include <audio/IAudioBuffer.hpp>
#include <audio/IAudioTrackManager.hpp>
using namespace CubA4::mod;

ModVanilla::ModVanilla(const IModInfo &modInfo) :
	modInfo_(modInfo)
{
	
}

ModVanilla::~ModVanilla()
{
	
}

void ModVanilla::load(std::shared_ptr<const ICore> core)
{
	core_ = core;
	manager_ = std::make_shared<manager::ModManager>();
	if (core_->getApplicationFlags() & ApplicationFlag::Render)
		renderStartup_.load(core, manager_);
	entitySetup_.load(core, manager_);
	blockSetup_.load(core, manager_);
	worldSetup_.load(core, manager_);
}

void ModVanilla::preinit(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	if (core_->getApplicationFlags() & ApplicationFlag::Render)
		renderStartup_.preinit(builder);
	entitySetup_.preinit(builder);
}

void ModVanilla::link(std::shared_ptr<const IModLinker> linker)
{

}

void ModVanilla::init(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	entitySetup_.init(builder);
	blockSetup_.init(builder);
	worldSetup_.init(builder);

	// test
	auto am = core_->getAudioManager();
	auto &amImporter = am->getImporter();
	auto &amTrackManager = am->getTrackManager();
	auto rm = core_->getResourcesManager();
	auto resource = rm->find("data/vanilla/assets/audio/meow.ogg");
	auto buffer = amImporter.importTrack(resource);
	audioTrack_ = amTrackManager.createTrack();
	audioTrack_->attachBuffer(buffer);
}

void ModVanilla::configure(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{

}

void ModVanilla::prefinish(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	core_->getLogger()->flush();
}

void ModVanilla::finish()
{
	worldSetup_.done();
	core_->getLogger()->flush();
}

void ModVanilla::start(CubA4::game::IGameControl &gameControl)
{
	gameControl_ = &gameControl;

	auto worldName = std::format("#{}@{}", ModVanillaId, "testWorld");
	auto dimName = std::format("#{}@{}/{}", ModVanillaId, "testWorld", "testDimension");
	gameControl_->requestWorldChange(worldName, dimName);

	auto dimId = worldSetup_.getTestDimensionId();

	auto playerFactory = manager_->getEntityManager()->getEntityFactory("player");

	CubA4::world::GlobalPosition pos1 = CubA4::world::BasePos<long double>(0, 80, 10);
	CubA4::world::GlobalPosition pos2 = CubA4::world::BasePos<long double>(0, 80, 20);

	auto player = gameControl_->requestSpawn(playerFactory, dimId, pos1);
	auto player2 = gameControl_->requestSpawn(playerFactory, dimId, pos2);

	CubA4::world::GlobalPosition pos;
	audioTrack_->play();
}

void ModVanilla::stop()
{
	gameControl_ = nullptr;
}

void ModVanilla::preunload()
{
	manager_.reset();
}

const IModInfo &ModVanilla::getInfo() const
{
	return modInfo_;
}

std::weak_ptr<const CubA4::manager::IModManager> ModVanilla::getManager() const
{
	return manager_;
}