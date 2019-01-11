#ifndef COREBASE_ICACHE_HPP
#define COREBASE_ICACHE_HPP

#include <memory>
#include <string>
#include "../filesystem/IAbstractDirectory.hpp"

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class ICacheResource;
			
			class ICache :
				public virtual CubA4::core::filesystem::IAbstractDirectory
			{
			public:
				virtual std::shared_ptr<ICacheResource> get(std::string path) const = 0;
				virtual std::shared_ptr<ICache> cd(std::string path) const = 0;
			protected:
				explicit ICache() = default;
				virtual ~ICache() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_ICACHE_HPP
