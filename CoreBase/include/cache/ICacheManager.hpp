#ifndef COREBASE_ICACHEMANAGER_HPP
#define COREBASE_ICACHEMANAGER_HPP

#include <memory>
#include <string>
#include "CacheType.hpp"

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class ICache;
			
			class ICacheManager
			{
			public:
				virtual std::shared_ptr<ICache> getResources(CacheType type, std::string moduleId) = 0;
			protected:
				explicit ICacheManager() = default;
				virtual ~ICacheManager() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_ICACHEMANAGER_HPP
