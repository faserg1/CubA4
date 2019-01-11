#ifndef CORE_RESOURCES_HPP
#define CORE_RESOURCES_HPP

#include <memory>
#include <resources/IResources.hpp>
#include "../filesystem/Directory.hpp"
#include <boost/filesystem.hpp>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class Resources :
				public virtual IResources, public CubA4::core::filesystem::Directory
			{
			public:
				explicit Resources(boost::filesystem::path path, bool createIfNotExists = false);
				~Resources();
				
				std::shared_ptr<const IResource> get(std::string path) const override;
				std::shared_ptr<IResources> cd(std::string path) const override;
			protected:
			private:
				const boost::filesystem::path path_;
			};
		}
	}
}

#endif // CORE_RESOURCES_HPP
