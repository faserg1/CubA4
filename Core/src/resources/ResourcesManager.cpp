#include "./ResourcesManager.hpp"
#include <algorithm>
using namespace CubA4::resources;

ResourcesManager::ResourcesManager()
{
	
}

ResourcesManager::~ResourcesManager()
{
	
}

void ResourcesManager::mount(ResourcesType type, Path path, std::shared_ptr<IResourceProvider> provider, Path cut)
{
	MountData data
	{
		.path = path,
		.cut = cut,
		.type = type,
		.provider = provider
	};

	providers_.push_back(data);
}

bool ResourcesManager::exists(Path path) const
{
	for (const auto &provider : findProvider(path))
	{
		auto cuttedPath = getCuttedPath(provider, path);
		if (provider.provider->exists(cuttedPath))
			return true;
	}
	return false;
}

std::shared_ptr<const IResource> ResourcesManager::find(Path path) const
{
	for (const auto &provider : findProvider(path))
	{
		auto cuttedPath = getCuttedPath(provider, path);
		if (auto resource = provider.provider->find(cuttedPath))
			return resource;
	}
	return {};
}

std::shared_ptr<IResource> ResourcesManager::edit(Path path) const
{
	for (const auto &provider : findProvider(path, true))
	{
		auto cuttedPath = getCuttedPath(provider, path);
		if (auto resource = provider.provider->edit(cuttedPath))
			return resource;
	}
	return {};
}

tl::generator<const ResourcesManager::MountData &> ResourcesManager::findProvider(Path path, bool write) const
{
	const auto filterFunction = [this, path, write](const MountData &providerData) -> bool
	{
		const std::vector<ResourcesType> allowedToWrite {ResourcesType::Cache, };
		if (write && std::find(allowedToWrite.begin(), allowedToWrite.end(), providerData.type) == allowedToWrite.end())
		{
			return false;
		}
		return isStartsWith(path, providerData.path);
	};
	decltype(providers_)::const_iterator it = providers_.begin();
	while (it != providers_.end())
	{
		it = std::find_if(it, providers_.end(), filterFunction);
		if (it != providers_.end())
		{
			auto &provider = *it;
			it++;
			co_yield provider;
		}
	}
}

Path ResourcesManager::getCuttedPath(const MountData &data, Path &path) const
{
	if (!isStartsWith(path, data.cut))
		return path;
	Path p;
	auto itPath = path.begin();
	auto itCut = data.cut.begin();
	while (itPath != path.end())
	{
		if (itCut != data.cut.end() && *itCut == *itPath)
		{
			itPath++;
			itCut++;
			continue;
		}
		if (p.empty())
			p += *itPath;
		else
			p /= *itPath;
		itPath++;
		if (itCut != data.cut.end())
			itCut++;
	}
	return p;
}

bool ResourcesManager::isStartsWith(const Path &full, const Path &beg) const
{
	auto itFull = full.begin();
	auto itBeg = beg.begin();
	while (itBeg != beg.end() && itFull != full.end())
	{
		if (*itBeg != *itFull)
			return false;
		itBeg++;
		itFull++;
	}
	return itBeg == beg.end();
}