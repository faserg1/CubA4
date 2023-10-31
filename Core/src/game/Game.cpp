#include <game/Game.hpp>
#include <game/IGameSubscriber.hpp>
#include <object/EntityManager.hpp>
#include <object/EntityRenderManager.hpp>
#include <Core.hpp>
#include <physics/PhysicsManager.hpp>
#include <chrono>
using namespace CubA4::game;

Game::Game(CubA4::Core &core, CubA4::core::IAppCallback &appCallback) :
	core_(core), appCallback_(appCallback), runGameLoop_(false), controller_(createController())
{
	
}

Game::~Game()
{
	
}

std::unique_ptr<CubA4::util::ISubscription> Game::subscribe(IGameSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

std::shared_ptr<const CubA4::game::controller::IController> Game::getController() const
{
	return controller_;
}

std::shared_ptr<CubA4::game::controller::IController> Game::getController()
{
	return controller_;
}

CubA4::object::IEntityRenderManager *Game::getEntityRenderManager() const
{
	if (!core_.getRenderManager() || !core_.getEntityManager())
		return nullptr;
	return &core_.getEntityManager()->getEntityRenderManager();
}

CubA4::object::IEntityManager *Game::getEntityManager() const
{
	if (!core_.getEntityManager())
		return nullptr;
	return core_.getEntityManager().get();
}

void Game::run()
{
	auto physicsManager = core_.getPhysicsManager();
	physicsManager->start();
	runGameLoop_ = true;
	gameThread_ = std::thread(&Game::loop, this);
}

void Game::stop()
{
	auto physicsManager = core_.getPhysicsManager();
	runGameLoop_ = false;
	gameThread_.join();
	physicsManager->stop();
}

void Game::setupEnvironment(std::shared_ptr<CubA4::core::Environment> env)
{
	env_ = env;
}

void Game::loop()
{
	using namespace std::chrono_literals;
	using Clock = std::chrono::steady_clock;
	using FloatSeconds = std::chrono::duration<float>;
	auto last = Clock::now();
	while (runGameLoop_)
	{
		std::this_thread::sleep_until(last + 1s / 20);
		auto current = Clock::now();
		auto interval = current - last;
		last = current;
		// TODO: make ticks back to integer
		iterate(std::chrono::duration_cast<FloatSeconds>(interval).count());
	}
}

void Game::iterate(float seconds)
{
	auto entityManager = core_.getEntityManager();
	// TODO: game tick for entity
}

std::shared_ptr<controller::Controller> Game::createController()
{
	if (auto appClientCallback = dynamic_cast<CubA4::core::IAppClientCallback*>(&appCallback_))
		return std::make_shared<CubA4::game::controller::Controller>(*appClientCallback);
	return {};
}