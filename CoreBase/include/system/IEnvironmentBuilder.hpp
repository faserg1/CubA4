#ifndef IENVIRONMENTBUILDER_HPP
#define IENVIRONMENTBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorld;
		}
	}

	namespace core
	{
		namespace system
		{
			class IEnvironmentBuilder
			{
			public:
				virtual void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) = 0;
			protected:
				explicit IEnvironmentBuilder() {}
				virtual ~IEnvironmentBuilder() {}
			private:
			};
		}
	}
}

#endif // IENVIRONMENTBUILDER_HPP
