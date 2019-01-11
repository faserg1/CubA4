#ifndef COREBASE_ICACHERESOURCE_HPP
#define COREBASE_ICACHERESOURCE_HPP

#include "../filesystem/IAbstractResource.hpp"

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class ICacheResource :
				public virtual filesystem::IAbstractResource
			{
			public:
				
			protected:
				explicit ICacheResource() = default;
				virtual ~ICacheResource() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_ICACHERESOURCE_HPP
