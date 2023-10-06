#include <engine/pipeline/RenderEntityPipeline.hpp>
#include <engine/compilers/RenderEntityCompiler.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/Transform.hpp>
#include <object/components/RenderInfoComponent.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/map.hpp>
using namespace CubA4::render::engine::pipeline;

RenderEntityPipeline::RenderEntityPipeline(std::shared_ptr<RenderEntityCompiler> entityCompiler) :
	entityCompiler_(entityCompiler)
{
	
}

void RenderEntityPipeline::onFramebufferUpdated(const RenderFramebufferData &data)
{
	framebufferData = data;

	for (auto &entity : entities_)
	{
		entity.second = entityCompiler_->recompileEntity(entity.second, data);
	}

	auto tf = [](auto sContainer) -> std::shared_ptr<const RenderEntity> { return sContainer; };
	std::vector entities = entities_ | ranges::views::values | ranges::views::transform(tf) | ranges::to<std::vector>;

	subHelper_.apply([&entities](IRenderEngineEntityPipelineSubscriber *sub)
	{
		sub->onRenderEntitiesUpdated(entities);
	});
}

uint32_t RenderEntityPipeline::getSubpassNumber() const
{
	return entityCompiler_->getSubpassNumber();
}

void RenderEntityPipeline::onEntityAdded(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render)
{
	if (!render.renderModel)
		return;
	auto id = render.renderModel->getId();
	if (auto it = entities_.find(id); it != entities_.end())
	{
		auto entity = it->second;
		std::vector<EntityInfo> infos;
		infos.emplace_back(
			tr,
			wi.factoryId,
			wi.entityId
		);
		auto renderEntity = entityCompiler_->extendEntity(entity, infos, render, framebufferData);
		entities_.insert_or_assign(id, renderEntity);
	}
	else
	{
		std::vector<EntityInfo> infos;
		infos.emplace_back(
			tr,
			wi.factoryId,
			wi.entityId
		);
		auto renderEntity = entityCompiler_->createEntity(infos, render, framebufferData);
		entities_.insert(std::make_pair(id, renderEntity));
	}

	auto tf = [](auto sContainer) -> std::shared_ptr<const RenderEntity> { return sContainer; };
	std::vector entities = entities_ | ranges::views::values | ranges::views::transform(tf) | ranges::to<std::vector>;

	subHelper_.apply([&entities](IRenderEngineEntityPipelineSubscriber *sub)
	{
		sub->onRenderEntitiesUpdated(entities);
	});
}

void RenderEntityPipeline::onEntityUpdated(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render)
{
	if (!render.renderModel)
		return;
	auto id = render.renderModel->getId();
	auto it = entities_.find(id);
	if (it == entities_.end())
		return;
	auto &entity = *it->second;

	entityCompiler_->updateEntity(tr, wi, entity);
}

void RenderEntityPipeline::onEntityRemoved(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render)
{
	if (!render.renderModel)
		return;
	auto id = render.renderModel->getId();
	auto it = entities_.find(id);
	if (it == entities_.end())
		return;
	auto &entity = *it->second;

	std::vector<EntityInfo> infos;
	infos.emplace_back(
		tr,
		wi.factoryId,
		wi.entityId
	);
	auto renderEntity = entityCompiler_->shrinkEntity(entity, infos, render, framebufferData);
	if (!renderEntity)
		entities_.erase(it);
	else
		entities_.insert_or_assign(id, renderEntity);
	
	auto tf = [](auto sContainer) -> std::shared_ptr<const RenderEntity> { return sContainer; };
	std::vector entities = entities_ | ranges::views::values | ranges::views::transform(tf) | ranges::to<std::vector>;

	subHelper_.apply([&entities](IRenderEngineEntityPipelineSubscriber *sub)
	{
		sub->onRenderEntitiesUpdated(entities);
	});
}

std::unique_ptr<CubA4::util::ISubscription> RenderEntityPipeline::subscribe(IRenderEngineEntityPipelineSubscriber *subscriber)
{
	return subHelper_.add(subscriber);
}