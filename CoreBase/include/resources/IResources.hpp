#ifndef COREBASE_IRESOURCES_HPP
#define COREBASE_IRESOURCES_HPP

#include <memory>
#include <string>
#include "../filesystem/IAbstractDirectory.hpp"

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResource;
			
			class IResources :
				public virtual CubA4::core::filesystem::IAbstractDirectory
			{
			public:
				virtual std::shared_ptr<IResource> get(std::string path) const = 0;
				virtual std::shared_ptr<IResources> cd(std::string path) const = 0;
			protected:
				explicit IResources() = default;
				virtual ~IResources() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IRESOURCES_HPP
