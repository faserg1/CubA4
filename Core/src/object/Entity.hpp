#pragma once

#include <vector>
#include <memory>
#include <object/IEntity.hpp>
#include <entt/entt.hpp>

namespace CubA4::object
{
	struct WorldInfo;

	class Entity : public virtual IEntity
	{
	public:
		Entity(entt::registry &registry, entt::entity entity);
		~Entity();

		IdType getEntityId() const override;
		IdType getFactoryId() const override;

		entt::registry &getRegistry() const;
		entt::entity getEntity() const;

		CameraComponent *getCameraComponent() override;
		const WorldInfo *getWorldInfoComponent() const;

		void enableControls() override;
		void disableControls() override;
		bool isControlsEnabled() const override;

		void forceDestroy();
	private:
		entt::registry &registry_;
		entt::entity entity_ = entt::null;

		bool controlsEnabled_;
	};
}