#pragma once

#include <memory>
#include <system/IEnvironmentBuilder.hpp>
#include "EnvironmentBuilderData.hpp"
#include "EnvironmentBuilderContext.hpp"

namespace CubA4::system
{
	class EnvironmentBuilder :
		public virtual IEnvironmentBuilder
	{
	public:
		explicit EnvironmentBuilder(EnvironmentBuilderData &data, const EnvironmentBuilderContext &context);
		~EnvironmentBuilder();

		const CubA4::render::IRenderInfo &getRenderInfo() const override;
		std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;

		bool registerObject(std::shared_ptr<const CubA4::object::IObject> object) override;
		std::shared_ptr<const CubA4::world::IWorld> createWorld(std::shared_ptr<const CubA4::world::IWorldDefinition> worldDef) override;
	protected:
	private:
		EnvironmentBuilderData &data_;
		const EnvironmentBuilderContext context_;
	};
}
