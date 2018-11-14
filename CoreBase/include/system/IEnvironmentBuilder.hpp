#ifndef IENVIRONMENTBUILDER_HPP
#define IENVIRONMENTBUILDER_HPP

#include <memory>
#include <string>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IObject;
		}

		namespace world
		{
			class IWorld;
			class IWorldDefinition;
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

				virtual bool registerObject(std::shared_ptr<const CubA4::mod::object::IObject> object) = 0;

				virtual std::shared_ptr<const CubA4::mod::world::IWorld> createWorld(std::shared_ptr<const CubA4::mod::world::IWorldDefinition> worldDef) = 0;
			protected:
				explicit IEnvironmentBuilder() = default;
				virtual ~IEnvironmentBuilder() = default;
			private:
			};
		}
	}
}

#endif // IENVIRONMENTBUILDER_HPP
