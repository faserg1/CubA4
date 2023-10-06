#pragma once

#include <memory>
#include <game/controller/IContextActionsRules.hpp>


namespace CubA4::object
{
	class IEntity;

	class EntityControllerRules : public virtual CubA4::game::controller::IContextActionsRules
	{
	public:
		EntityControllerRules(std::shared_ptr<const IEntity> entity, std::shared_ptr<CubA4::game::controller::IContextActionsRules> childRules);

		bool checkContext(const CubA4::game::controller::IContext &context) const override;
	private:
		const std::weak_ptr<const IEntity> entity_;
		const std::shared_ptr<CubA4::game::controller::IContextActionsRules> childRules_;
	};
}