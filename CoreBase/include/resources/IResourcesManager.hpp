#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <resources/IResource.hpp>
#include <resources/IResourceProvider.hpp>
#include <resources/ResourcesType.hpp>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResource;
			class IResourceProvider;
			
			class IResourcesManager : public IResourceProvider
			{
			public:
				virtual void mount(ResourcesType type, Path path, std::shared_ptr<IResourceProvider> provider, Path cut = {}) = 0;
			protected:
				explicit IResourcesManager() = default;
				virtual ~IResourcesManager() = default;
			private:
			};
		}
	}
}

