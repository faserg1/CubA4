#ifndef COREBASE_IRESOURCESMANAGER_HPP
#define COREBASE_IRESOURCESMANAGER_HPP

#include <memory>
#include <string>
#include "ResourcesType.hpp"

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResources;
			
			class IResourcesManager
			{
			public:
				virtual std::shared_ptr<IResources> getResources(ResourcesType type, std::string moduleId) = 0;
			protected:
				explicit IResourcesManager() = default;
				virtual ~IResourcesManager() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IRESOURCESMANAGER_HPP
