#include <engine/render/EntitySubRenderPipeline.hpp>
#include <engine/pipeline/RenderEntityPipeline.hpp>
#include <engine/world/RenderEntity.hpp>
using namespace CubA4::render::engine::pipeline;

EntitySubRenderPipeline::EntitySubRenderPipeline(std::shared_ptr<RenderEntityPipeline> renderEntityPipeline, SubpipelineVersion incrementCount) :
	subpass_(renderEntityPipeline->getSubpassNumber()), incrementCount_(incrementCount)
{
	entityUpdateSubscription_ = renderEntityPipeline->subscribe(this);
}

EntitySubRenderPipeline::~EntitySubRenderPipeline() = default;

std::string EntitySubRenderPipeline::debugName() const
{
	return "EntitySubRenderPipeline";
}

std::array<float, 4> EntitySubRenderPipeline::debugColor() const
{
	return {0.f, 0.f, 0.5f, 1.f};
}

void EntitySubRenderPipeline::onIterate()
{
	auto locker = oldEntitiesLock_.lock();
	auto it = std::remove_if(oldEntities_.begin(), oldEntities_.end(), [](OldEntitiesInfo &oldInfo) -> bool
	{
		if (oldInfo.cyclesLeft > 0)
			oldInfo.cyclesLeft--;
		return !oldInfo.cyclesLeft;
	});
	oldEntities_.erase(it, oldEntities_.end());
}

void EntitySubRenderPipeline::executeFrom(VkCommandBuffer primaryCmdBuffer)
{
	decltype(entities_) entities;

	{
		auto locker = entitiesLock_.lock();
		entities = entities_;
	}

	for (auto entity : entities)
	{
		if (!entity)
			continue;
		entity->executeFrom(primaryCmdBuffer);
	}
}

uint32_t EntitySubRenderPipeline::getSubpass() const
{
	return subpass_;
}

EntitySubRenderPipeline::SubpipelineVersion EntitySubRenderPipeline::getVersion() const
{
	return version_;
}

void EntitySubRenderPipeline::onRenderEntitiesUpdated(const std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderEntity>> &entities)
{
	{
		auto locker = entitiesLock_.lock();
		auto locker2 = oldEntitiesLock_.lock();
		oldEntities_.push_back(OldEntitiesInfo {
			.cyclesLeft = 10,
			.oldEntities = entities_
		});
		entities_ = entities;
	}
	version_.fetch_add(incrementCount_);
}