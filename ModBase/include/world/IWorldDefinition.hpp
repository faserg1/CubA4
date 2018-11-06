#ifndef IWORLDDEFINITION_HPP
#define IWORLDDEFINITION_HPP

#include <string>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorldDefinition
			{
			public:
				virtual std::string getId() const = 0;
				virtual std::wstring getName() const = 0;
			protected:
				explicit IWorldDefinition() = default;
				virtual ~IWorldDefinition() = default;
			private:
			};
		}
	}
}

#endif // IWORLDDEFINITION_HPP
