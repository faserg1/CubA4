#ifndef MODBASE_IWORLDDEFINITION_HPP
#define MODBASE_IWORLDDEFINITION_HPP

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

#endif // MODBASE_IWORLDDEFINITION_HPP
