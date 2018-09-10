#ifndef ENVIRONMENTBUILDER_HPP
#define ENVIRONMENTBUILDER_HPP

#include <memory>
#include <system/IEnvironmentBuilder.hpp>

namespace CubA4
{
	namespace render
	{
		class IRenderInfo;

		namespace engine
		{
			class IRenderManager;
		}
	}

	namespace core
	{
		namespace system
		{
			class EnvironmentBuilder :
				public virtual IEnvironmentBuilder
			{
			public:
				explicit EnvironmentBuilder(std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager, const CubA4::render::IRenderInfo &renderInfo);
				~EnvironmentBuilder();

				const CubA4::render::IRenderInfo &getRenderInfo() const override;
				std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const override;

				void registerModel(std::shared_ptr<const CubA4::core::model::IModel> model) override;
				void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) override;
			protected:
			private:
				const CubA4::render::IRenderInfo &renderInfo_;
				const std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager_;
			};
		}
	}
}

#endif // ENVIRONMENTBUILDER_HPP
