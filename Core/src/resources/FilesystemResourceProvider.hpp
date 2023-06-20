#pragma once

#include <resources/IResourceProvider.hpp>
#include <filesystem>

namespace CubA4::resources
{
	class FilesystemResourceProvider : public virtual IResourceProvider
	{
	public:
		explicit FilesystemResourceProvider(Path realPath);
		~FilesystemResourceProvider();

		void onMount(Path from) override;
		void onUnMount() override;
		bool exists(Path path) const override;
		std::shared_ptr<const IResource> find(Path path) const override;
		std::shared_ptr<IResource> edit(Path path) const override;
	private:
		Path getFullPath(Path path) const;
	private:
		const Path basePath_;
		Path mountedTo_;
	};
}
