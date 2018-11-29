#ifndef TESTWORLD_HPP
#define TESTWORLD_HPP

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

#endif // TESTWORLD_HPP