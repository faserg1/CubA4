#pragma once

#include <memory>
#include <resources/IResourcesManager.hpp>
#include <vector>
#include <tl/generator.hpp>

namespace CubA4::resources
{
	class ResourcesManager :
		public virtual IResourcesManager
	{
		struct MountData
		{
			Path path;
			Path cut;
			ResourcesType type;
			std::shared_ptr<IResourceProvider> provider;
		};
	public:
		explicit ResourcesManager();
		~ResourcesManager();
		
		void mount(ResourcesType type, Path path, std::shared_ptr<IResourceProvider> provider, Path cut = {}) override;

		bool exists(Path path) const override;
		std::shared_ptr<const IResource> find(Path path) const override;
		std::shared_ptr<IResource> edit(Path path) const override;
	protected:
		tl::generator<const MountData &> findProvider(Path path, bool write = false) const;
		Path getCuttedPath(const MountData &data, Path &path) const;
		bool isStartsWith(const Path &full, const Path &beg) const;
	private:
		std::vector<MountData> providers_;
	};
}
