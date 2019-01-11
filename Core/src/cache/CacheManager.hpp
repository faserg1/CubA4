#ifndef CORE_CACHEMANAGER_HPP
#define CORE_CACHEMANAGER_HPP

#include <memory>
#include <boost/filesystem.hpp>
#include <cache/ICacheManager.hpp>

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class CacheManager :
				public virtual ICacheManager
			{
			public:
				explicit CacheManager(boost::filesystem::path path);
				~CacheManager();
				
				std::shared_ptr<ICache> getResources(CacheType type, std::string moduleId) override;
			protected:
			private:
				const boost::filesystem::path path_;
			};
		}
	}
}

#endif // CORE_CACHEMANAGER_HPP
