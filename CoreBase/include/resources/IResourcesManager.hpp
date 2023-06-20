#pragma once

#include <memory>
#include <string>
#include <filesystem>
#include <resources/IResource.hpp>
#include <resources/IResourceProvider.hpp>
#include <resources/ResourcesType.hpp>

namespace CubA4::resources
{
	class IResourcesManager : public IResourceProvider
	{
	public:
		virtual void mount(ResourcesType type, Path path, std::shared_ptr<IResourceProvider> provider, Path cut = {}) = 0;
	protected:
		explicit IResourcesManager() = default;
		virtual ~IResourcesManager() = default;
	private:
		void onMount(Path from) final {}
		void onUnMount() final {}
	};
}


