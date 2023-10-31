#include "ModVanilla.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <ModVanillaConst.hpp>
#include <ModControl.hpp>
#include <fmt/format.h>
#include <audio/IAudioImporter.hpp>
#include <audio/IAudioBuffer.hpp>
#include <audio/IAudioTrackManager.hpp>
#include <physics/IPhysicsEntityControllerWrapper.hpp>
#include <object/components/CameraComponent.hpp>
#include <engine/world/ICamera.hpp>
#include <engine/world/IWorldManager.hpp>
#include <engine/IRenderManager.hpp>
#include <future>
using namespace CubA4::mod;

ModVanilla::ModVanilla(const IModInfo &modInfo) :
	modInfo_(modInfo), modControl_(std::make_shared<ModControl>()),
	entitySetup_(modControl_)
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
	{
		renderStartup_.preinit(builder);
	}
		
	entitySetup_.preinit(builder);
}

void ModVanilla::link(const IModLinker &linker)
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
	audioTrack_->setVolume(0.5);
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
	modControl_->setGameControl(&gameControl);

	auto worldName = std::format("#{}@{}", ModVanillaId, "testWorld");
	auto dimName = std::format("#{}@{}/{}", ModVanillaId, "testWorld", "testDimension");
	gameControl.requestWorldChange(worldName, dimName);

	static auto startLater = std::async(std::launch::async, [this]()
	{
		startInternal();
	});
}

void ModVanilla::stop()
{
	modControl_->setGameControl(nullptr);
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

void ModVanilla::startInternal()
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(3s);

	CubA4::world::GlobalPosition pos;
	audioTrack_->play();

	auto dimId = worldSetup_.getTestDimensionId();

	auto cubeFactory = manager_->getEntityManager()->getEntityFactory("cube");
	auto playerFactory = manager_->getEntityManager()->getEntityFactory("player");

	CubA4::world::GlobalPosition cubePos = CubA4::world::BasePos<long double>(0, 80, 10);
	CubA4::world::GlobalPosition playerPos = CubA4::world::BasePos<long double>(0, 20, 0);

	auto *gameControl = modControl_->getGameControl();
	if (!gameControl)
		return;

	auto cube = gameControl->requestSpawn(cubeFactory, dimId, cubePos);
	auto player = gameControl->requestSpawn(playerFactory, dimId, playerPos);
	player->enableControls();

	if (auto cameraComponent = player->getCameraComponent(); cameraComponent && core_->getApplicationFlags() & ApplicationFlag::Render)
	{
		renderStartup_.getRenderManager()->getWorldManager()->setActiveCamera(cameraComponent->camera);
	}
}