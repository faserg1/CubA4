#ifndef ENVIRONMENTBUILDER_HPP
#define ENVIRONMENTBUILDER_HPP

#include <memory>
#include <system/IEnvironmentBuilder.hpp>
#include "EnvironmentBuilderData.hpp"
#include "EnvironmentBuilderContext.hpp"

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class EnvironmentBuilder :
				public virtual IEnvironmentBuilder
			{
			public:
				explicit EnvironmentBuilder(const EnvironmentBuilderData &data, const EnvironmentBuilderContext &context);
				~EnvironmentBuilder();

				const CubA4::render::IRenderInfo &getRenderInfo() const override;
				std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;

				void registerBlock(std::shared_ptr<const CubA4::mod::object::IBlock> block) override;
				void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) override;
			protected:
			private:
				const EnvironmentBuilderData data_;
				const EnvironmentBuilderContext context_;
			};
		}
	}
}

#endif // ENVIRONMENTBUILDER_HPP
