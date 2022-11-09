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

void CubA4::app::AppStartup::nextMainLoopIteration()
{
	doSomeTestThings();
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
	//wm->setCameraPosition({-2,0,0}, 0, 10, 0);
}

void AppStartup::stop()
{
	startup_->stop();
	auto renderEngine = renderEngine_.lock();
	renderEngine->stop();
}

void AppStartup::doSomeTestThings()
{
	auto renderEngine = renderEngine_.lock();
	constexpr const float max = 4;
	static float l = -max;
	const float speed = 0.005f;
	static bool up = true;
	if (up)
		l += speed;
	else
		l -= speed;
	if (l > max)
		up = false;
	else if (l < -max)
		up = true;
	auto rm = renderEngine->getRenderManager();
	auto wm = rm->getWorldManager();
	double cl = clock();
	//wm->setCameraRotation(0, 0, cl / CLOCKS_PER_SEC);
	double x = sin(cl / CLOCKS_PER_SEC) * 10;
	double z = cos(cl / CLOCKS_PER_SEC) * 10;
	wm->setCameraPosition({ 0, 0, 0 }, static_cast<float>(x), l, static_cast<float>(z));
}