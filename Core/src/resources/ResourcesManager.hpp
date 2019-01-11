#ifndef CORE_RESOURCESMANAGER_HPP
#define CORE_RESOURCESMANAGER_HPP

#include <memory>
#include <boost/filesystem.hpp>
#include <resources/IResourcesManager.hpp>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class ResourcesManager :
				public virtual IResourcesManager
			{
			public:
				explicit ResourcesManager(boost::filesystem::path path);
				~ResourcesManager();
				
				std::shared_ptr<IResources> getResources(ResourcesType type, std::string moduleId) override;
			protected:
			private:
				const boost::filesystem::path path_;
			};
		}
	}
}

#endif // CORE_RESOURCESMANAGER_HPP
