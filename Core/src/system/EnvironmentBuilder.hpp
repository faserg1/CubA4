#pragma once

#include <memory>
#include <system/IEnvironmentBuilder.hpp>
#include <Core.hpp>
#include "EnvironmentBuilderData.hpp"
#include "EnvironmentBuilderContext.hpp"

namespace CubA4::system
{
	class EnvironmentBuilder :
		public virtual IEnvironmentBuilder
	{
	public:
		explicit EnvironmentBuilder(Core &core, EnvironmentBuilderData &data, const EnvironmentBuilderContext &context);
		~EnvironmentBuilder();

		const CubA4::render::IRenderInfo &getRenderInfo() const override;
		std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;
		std::shared_ptr<CubA4::game::controller::IRootActions> getActions() const override;

		bool registerObject(std::shared_ptr<CubA4::object::IObject> object) override;
		std::shared_ptr<const CubA4::world::IWorld> createWorld(std::shared_ptr<const CubA4::world::IWorldDefinition> worldDef) override;
	protected:
	private:
		Core &core_;
		EnvironmentBuilderData &data_;
		const EnvironmentBuilderContext context_;
	};
}
