#pragma once

#include <resources/IResource.hpp>

namespace CubA4::resources
{
	class IResourceProvider
	{
	public:
		virtual ~IResourceProvider() = default;

		virtual bool exists(Path path) const = 0;
		virtual std::shared_ptr<const IResource> find(Path path) const = 0;
		virtual std::shared_ptr<IResource> edit(Path path) const = 0;
	protected:
		explicit IResourceProvider() = default;
	};
}

