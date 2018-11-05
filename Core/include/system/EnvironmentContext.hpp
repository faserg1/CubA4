#ifndef ENVIRONMENTCONTEXT_HPP
#define ENVIRONMENTCONTEXT_HPP

#include "IdentityMap.hpp"

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class EnvironmentContext
			{
			public:
				explicit EnvironmentContext(const IdentityMap &map);
				~EnvironmentContext();
			protected:
			private:
				const IdentityMap map_;
			};
		}
	}
}

#endif // ENVIRONMENTCONTEXT_HPP
