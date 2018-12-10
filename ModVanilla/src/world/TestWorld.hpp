#ifndef MODVANILLA_TESTWORLD_HPP
#define MODVANILLA_TESTWORLD_HPP

#include <world/IWorldDefinition.hpp>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class TestWorld :
				public virtual IWorldDefinition
			{
			public:
				explicit TestWorld();
				~TestWorld();

				std::string getId() const override;
				std::wstring getName() const override;
			protected:
			private:
			};
		}
	}
}

#endif // MODVANILLA_TESTWORLD_HPP
