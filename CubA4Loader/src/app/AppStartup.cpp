#include "./AppStartup.hpp"
#include <system/IAppCallback.hpp>
#include <system/IStartup.hpp>
#include <engine/IRenderEngine.hpp>
#include <CommonFactory.hpp>


//TODO: [OOKAMI] Загловки для теста
#include <engine/IRenderManager.hpp>
#include <engine/world/IWorldManager.hpp>
#include <ctime>
#include <cmath>
#include <fmt/format.h>

using namespace CubA4::app;

AppStartup::AppStartup(CubA4::system::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core,
	std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine) :
	appCallback_(appCallback), core_(core), renderEngine_(renderEngine),
	startup_(CubA4::CommonFactory::createStartup(core))
{
	startup_->load(appCallback_);
	setup();
}

AppStartup::~AppStartup()
{
	shutdown();
}

void AppStartup::keyChanged(CubA4::game::controller::Button btn, CubA4::game::controller::BMods mods, bool pressed)
{
	startup_->getGame()->getController()->onButtonChanged(btn, mods, pressed);
}

void AppStartup::mouseMove(int32_t x, int32_t y, bool relative)
{
	if (relative)
		startup_->getGame()->getController()->onMove(CubA4::game::controller::AxisBinding::MOUSE, x, y);
	else
		startup_->getGame()->getController()->onPosition(x, y);
}

void CubA4::app::AppStartup::nextMainLoopIteration(double delta)
{
	doSomeTestThings(delta);
}

bool AppStartup::setup()
{
	startup_->setup();
	if (!setupGame())
		return false;
	run();
	return true;
}

void AppStartup::shutdown()
{
	stop();
	shutdownGame();
	startup_->shutdown();
}

bool AppStartup::setupGame()
{
	auto renderEngine = renderEngine_.lock();
	renderEngine->setGame(startup_->getGame());
	auto rm = renderEngine->getRenderManager();
	auto wm = rm->getWorldManager();
	camera_ = wm->createCamera();
	wm->setActiveCamera(camera_);
	static auto sub2 = startup_->getGame()->getController()->getActions()->addActionCallback("mouse", [this]()
	{
		static auto request = false;
		startup_->getGame()->getController()->requestMouseCapture(!request);
		request = !request;
	});
	
	// test thing
	static auto sub = startup_->getGame()->getController()->getActions()->addActionAxisCallback("camera", [this](int64_t x, int64_t y){
		float sensivity = 0.05f;
		camera_->rotate(0, y * sensivity, x * sensivity);
	});
	return true;
}

void AppStartup::shutdownGame()
{
	auto renderEngine = renderEngine_.lock();
	renderEngine->setGame({});
}

void AppStartup::run()
{
	auto renderEngine = renderEngine_.lock();
	renderEngine->run();
	startup_->run();

	//TODO: [OOKAMI] Убрать тестовые вещи
	auto rm = renderEngine->getRenderManager();
	auto wm = rm->getWorldManager();
	wm->setFieldOfView(60);
}

void AppStartup::stop()
{
	startup_->stop();
	auto renderEngine = renderEngine_.lock();
	renderEngine->stop();
}

void AppStartup::doSomeTestThings(double delta)
{
	const auto speed = 0.05f;
	const auto vel = speed * delta;
	if (startup_->getGame()->getController()->getActionState("forward"))
		camera_->move(0.f, 0.f, -vel);
	if (startup_->getGame()->getController()->getActionState("back"))
		camera_->move(0.f, 0.f, vel);
	if (startup_->getGame()->getController()->getActionState("left"))
		camera_->move(-vel, 0.f, 0.f);
	if (startup_->getGame()->getController()->getActionState("right"))
		camera_->move(vel, 0.f, 0.f);
}