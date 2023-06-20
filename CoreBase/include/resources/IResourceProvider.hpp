#pragma once

#include <resources/IResource.hpp>

namespace CubA4::resources
{
	class IResourceProvider
	{
	public:
		virtual ~IResourceProvider() = default;

		virtual void onMount(Path from) = 0;
		virtual void onUnMount() = 0;
		virtual bool exists(Path path) const = 0;
		virtual std::shared_ptr<const IResource> find(Path path) const = 0;
		virtual std::shared_ptr<IResource> edit(Path path) const = 0;
	protected:
		explicit IResourceProvider() = default;
	};
}

