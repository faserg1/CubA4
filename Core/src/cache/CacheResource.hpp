#ifndef CORE_CACHERESOURCE_HPP
#define CORE_CACHERESOURCE_HPP

#include <memory>
#include <boost/filesystem.hpp>
#include <cache/ICacheResource.hpp>
#include "../filesystem/File.hpp"

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class CacheResource :
				public virtual ICacheResource, public filesystem::File
			{
			public:
				explicit CacheResource(boost::filesystem::path);
				~CacheResource();
			protected:
			private:
			};
		}
	}
}

#endif // CORE_CACHERESOURCE_HPP
