#pragma once

#include <entt/entt.hpp>
#include <util/SubscriptionHelper.hpp>
#include <object/IEntityRenderManager.hpp>

namespace CubA4::object
{
	class EntityRenderManager :
		public virtual IEntityRenderManager
	{
	public:
		explicit EntityRenderManager(entt::registry &registry);
		~EntityRenderManager();

		std::unique_ptr<util::ISubscription> subscribe(CubA4::render::engine::pipeline::IRenderEntitySubscriber *subscriber) override;
	private:
		void onRenderEntityAdded(entt::registry &registry, entt::entity entity);
		void onRenderEntityUpdated(entt::registry &registry, entt::entity entity);
		void onRenderEntityRemoved(entt::registry &registry, entt::entity entity);
	private:
		entt::registry &registry_;
		entt::connection onRenderEntityAdded_;
		entt::connection onRenderEntityUpdated_;
		entt::connection onRenderEntityRemoved_;

		util::SubscriptionHelper<CubA4::render::engine::pipeline::IRenderEntitySubscriber> subHolder_;
	};
}