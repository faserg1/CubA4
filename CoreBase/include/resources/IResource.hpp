#ifndef COREBASE_IRESOURCE_HPP
#define COREBASE_IRESOURCE_HPP

#include "../filesystem/IAbstractResource.hpp"

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResource :
				public virtual filesystem::IAbstractResource
			{
			public:
				
			protected:
				explicit IResource() = default;
				virtual ~IResource() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IRESOURCE_HPP
