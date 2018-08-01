#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <system/IEnvironment.hpp>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class Environment :
				public virtual IEnvironment
			{
			public:
				explicit Environment();
				~Environment();
			protected:
			private:
			};
		}
	}
}

#endif // ENVIRONMENT_HPP
