#ifndef CORE_CACHE_HPP
#define CORE_CACHE_HPP

#include <memory>
#include <cache/ICache.hpp>
#include "../filesystem/Directory.hpp"
#include <boost/filesystem.hpp>

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			class Cache :
				public virtual ICache, public filesystem::Directory
			{
			public:
				explicit Cache(boost::filesystem::path path, bool createIfNotExists = false);
				~Cache();
				
				std::shared_ptr<ICacheResource> get(std::string path) const override;
				std::shared_ptr<ICache> cd(std::string path) const override;
			protected:
			private:
				const boost::filesystem::path_;
			};
		}
	}
}

#endif // CORE_CACHE_HPP
