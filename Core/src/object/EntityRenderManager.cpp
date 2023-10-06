#include <object/EntityRenderManager.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/Transform.hpp>
#include <object/components/CameraComponent.hpp>
#include <engine/pipeline/IRenderEntitySubscriber.hpp>
using namespace CubA4::object;
using namespace CubA4::world;

EntityRenderManager::EntityRenderManager(entt::registry &registry) :
	registry_(registry)
{
	onRenderEntityAdded_ = registry.on_construct<RenderInfoComponent>().connect<&EntityRenderManager::onRenderEntityAdded>(this);
	onRenderEntityUpdated_ = registry.on_update<RenderInfoComponent>().connect<&EntityRenderManager::onRenderEntityUpdated>(this);
	onRenderEntityUpdated_ = registry.on_update<Transform>().connect<&EntityRenderManager::onRenderEntityUpdated>(this);
	onRenderEntityRemoved_ = registry.on_destroy<RenderInfoComponent>().connect<&EntityRenderManager::onRenderEntityRemoved>(this);
}

EntityRenderManager::~EntityRenderManager() = default;

std::unique_ptr<CubA4::util::ISubscription> EntityRenderManager::subscribe(CubA4::render::engine::pipeline::IRenderEntitySubscriber *subscriber)
{
	return subHolder_.add(subscriber);
}

void EntityRenderManager::onRenderEntityAdded(entt::registry &registry, entt::entity entity)
{
	subHolder_.apply([&registry, entity](CubA4::render::engine::pipeline::IRenderEntitySubscriber *sub)
	{
		auto [transform, worldInfo, render] = registry.get<Transform, WorldInfo, RenderInfoComponent>(entity);
		sub->onEntityAdded(transform, worldInfo, render);
	});
}

void EntityRenderManager::onRenderEntityUpdated(entt::registry &registry, entt::entity entity)
{
	subHolder_.apply([&registry, entity](CubA4::render::engine::pipeline::IRenderEntitySubscriber *sub)
	{
		auto [transform, worldInfo, render] = registry.get<Transform, WorldInfo, RenderInfoComponent>(entity);
		sub->onEntityUpdated(transform, worldInfo, render);
	});

	if (auto cameraComponent = registry.try_get<CameraComponent>(entity))
	{
		auto transform = registry.get<Transform>(entity);
		// TODO: update camera rotation
		cameraComponent->camera->setPosition(transform.position - GlobalPosition(0.5f, 0.f, 0.f));
	}
}

void EntityRenderManager::onRenderEntityRemoved(entt::registry &registry, entt::entity entity)
{
	subHolder_.apply([&registry, entity](CubA4::render::engine::pipeline::IRenderEntitySubscriber *sub)
	{
		auto [transform, worldInfo, render] = registry.get<Transform, WorldInfo, RenderInfoComponent>(entity);
		sub->onEntityRemoved(transform, worldInfo, render);
	});
}