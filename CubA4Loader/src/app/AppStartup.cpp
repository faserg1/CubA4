#include "./AppStartup.hpp"
#include <core/IAppCallback.hpp>
#include <core/IStartup.hpp>
#include <engine/IRenderEngine.hpp>
#include <CommonFactory.hpp>


//TODO: [OOKAMI] Загловки для теста
#include <engine/IRenderManager.hpp>
#include <ui/IRenderUIManager.hpp>
#include <engine/world/IWorldManager.hpp>
#include <engine/debug/IRenderDebug.hpp>
#include <ctime>
#include <cmath>
#include <fmt/format.h>
#include <world/IDimension.hpp>

using namespace CubA4::app;

AppStartup::AppStartup(CubA4::core::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core,
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

std::shared_ptr<CubA4::core::IStartup> AppStartup::getSystemStartup()
{
	return startup_;
}

void AppStartup::nextMainLoopIteration(double delta)
{
	doSomeTestThings(delta);
}

bool AppStartup::setup()
{
	startup_->setup();
	if (!setupGame())
		return false;
	/// test
	startup_->getGame()->getController()->getBindings()->addKeyBinding("mouse", CubA4::game::controller::Button::F1, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("uitoggle", CubA4::game::controller::Button::F2, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("debuguitoggle", CubA4::game::controller::Button::F3, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("forward", CubA4::game::controller::Button::W, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("back", CubA4::game::controller::Button::S, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("left", CubA4::game::controller::Button::A, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("right", CubA4::game::controller::Button::D, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("up", CubA4::game::controller::Button::Space, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("down", CubA4::game::controller::Button::CtrlLeft, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("click", CubA4::game::controller::Button::LMB, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addKeyBinding("click2", CubA4::game::controller::Button::RMB, 0 | CubA4::game::controller::BMod::None);
	startup_->getGame()->getController()->getBindings()->addAxisBinding("camera", CubA4::game::controller::AxisBinding::MOUSE);
	/// end test
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

	static auto sub2 = startup_->getGame()->getController()->getRootActions()->addActionCallback("mouse", [this]()
	{
		static auto request = false;
		startup_->getGame()->getController()->requestMouseCapture(!request);
		request = !request;
	});

	static auto sub3 = startup_->getGame()->getController()->getRootActions()->addActionCallback("uitoggle", [this, weakRm = std::weak_ptr(rm)]()
	{
		if (auto rm = weakRm.lock())
		{
			rm->getUIManager()->getMainCanvas()->toggleVisibility();
		}
	});

	static auto sub4 = startup_->getGame()->getController()->getRootActions()->addActionPositionCallback("click", [this, weakRm = std::weak_ptr(rm)](int32_t x, int32_t y)
	{
		using namespace CubA4::render::engine::debug;
		static std::vector<std::shared_ptr<IRenderDebugCollection>> collections;
		if (auto rm = weakRm.lock())
		{
			auto world = rm->getWorldManager();
			auto debug = rm->getDebug();

			auto ray = world->getRayFrom(x, y);
			auto fPos = ray.position.inBlockPos() + ray.position.blockPosition();
			auto fPosTo = ray.direction * CubA4::world::ChunkSize + fPos;

			if (auto core = core_.lock())
			{
				auto dimName = std::format("#{}@{}/{}", "vanilla", "testWorld", "testDimension");
				auto dim = core->getEnvironment()->getObjectT<CubA4::world::IDimension>(dimName);
				dim->closestBlockRayTest(ray.position, CubA4::world::GlobalPosition(fPosTo));
			}

			auto col = debug->addCollection();
			
			col->addLine(ray.position.chunkPos(), fPos, fPosTo);
			collections.push_back(col);
		}
	});
	
	
	static auto sub = startup_->getGame()->getController()->getRootActions()->addActionAxisCallback("camera", [this](int64_t x, int64_t y){
		float sensivity = 0.05f;
		camera_->rotate(0, -y * sensivity, x * sensivity);
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
	//TODO: [OOKAMI] Убрать тестовые вещи
	const auto speed = 0.05f;
	const auto vel = speed * delta;
	if (!delta)
		return;
	if (startup_->getGame()->getController()->getActionState("forward"))
		camera_->move(0.f, 0.f, static_cast<float>(vel));
	if (startup_->getGame()->getController()->getActionState("back"))
		camera_->move(0.f, 0.f, static_cast<float>(-vel));
	if (startup_->getGame()->getController()->getActionState("left"))
		camera_->move(static_cast<float>(-vel), 0.f, 0.f);
	if (startup_->getGame()->getController()->getActionState("right"))
		camera_->move(static_cast<float>(vel), 0.f, 0.f);
	if (startup_->getGame()->getController()->getActionState("up"))
		camera_->move(0.f, static_cast<float>(vel), 0.f);
	if (startup_->getGame()->getController()->getActionState("down"))
		camera_->move(0.f, static_cast<float>(-vel), 0.f);
}