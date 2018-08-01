#ifndef ENVIRONMENTBUILDER_HPP
#define ENVIRONMENTBUILDER_HPP

#include <system/IEnvironmentBuilder.hpp>

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
				explicit EnvironmentBuilder();
				~EnvironmentBuilder();
			protected:
			private:
			};
		}
	}
}

#endif // ENVIRONMENTBUILDER_HPP
