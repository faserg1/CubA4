#ifndef IENVIRONMENTBUILDER_HPP
#define IENVIRONMENTBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IBlock;
			class IEntity;
			class IItem;
		}

		namespace world
		{
			class IWorld;
		}
	}

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
			class IEnvironmentBuilder
			{
			public:
				virtual const CubA4::render::IRenderInfo &getRenderInfo() const = 0;
				virtual std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const = 0;

				virtual void registerBlock(std::shared_ptr<const CubA4::mod::object::IBlock> block) = 0;

				virtual void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) = 0;
			protected:
				explicit IEnvironmentBuilder() = default;
				virtual ~IEnvironmentBuilder() = default;
			private:
			};
		}
	}
}

#endif // IENVIRONMENTBUILDER_HPP
